/*
   Copyright 2022 Eduardo Ibarra

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "BVH.h"

#include <algorithm>
#include <queue>

enum AXIS {
    X = 0,
    Z = 1
    //Z = 2
};

constexpr AXIS toAxis(int i) {
    return static_cast<AXIS>(i % 2);
}

struct SphereLess {
    AXIS axis;

    bool operator()(const std::shared_ptr<Sphere>& s1, const std::shared_ptr<Sphere>& s2) const {
        switch (axis) {
            case X: return s1->position().x < s2->position().x;
            //case Y: return s1->position().y < s2->position().y;
            case Z: return s1->position().z < s2->position().z;
        }

        return false;
    }
};

void BVH::add(const std::shared_ptr<Sphere>& s)
{
    m_root.m_boundingBox.fit(*s);
    m_root.m_spheres.push_back(s);
}

void BVH::process()
{
    SphereLess less;
    std::queue<Node*> splitQ;
    splitQ.push(&m_root);

    int counter = 0;
    while(!splitQ.empty()) {
        less.axis = toAxis(counter++);
        Node* curNode = splitQ.front();
        splitQ.pop();

        if(curNode->m_spheres.size() <= MAX_SPHERES) {
            continue;
        }

        std::sort(curNode->m_spheres.begin(), curNode->m_spheres.end(), less);

        curNode->m_left = std::make_unique<Node>();
        curNode->m_right = std::make_unique<Node>();

        for(size_t i = 0; i < curNode->m_spheres.size(); i++) {
            Node* toAdd = curNode->m_left.get();

            if(i > curNode->m_spheres.size() / 2) {
                toAdd = curNode->m_right.get();
            }

            toAdd->m_boundingBox.fit(*curNode->m_spheres[i]);
            toAdd->m_spheres.push_back(curNode->m_spheres[i]);
        }

        curNode->m_spheres.clear();
        splitQ.push(curNode->m_left.get());
        splitQ.push(curNode->m_right.get());
    }
}

size_t BVH::coarseIntersect(std::vector<std::shared_ptr<Sphere>>& potiential_spheres, const Ray& ray) const {
    size_t numIntersections = 0;
    potiential_spheres.clear();
    std::queue<const Node*> q;
    q.push(&m_root);

    while(!q.empty()) {
        const Node* curNode = q.front();
        q.pop();

        numIntersections++;
        if(!curNode->m_boundingBox.intersect(ray)) {
            continue;
        }

        if(curNode->m_left) {
            q.push(curNode->m_left.get());
        }

        if(curNode->m_right) {
            q.push(curNode->m_right.get());
        }

        if(!curNode->m_spheres.empty()) {
            for(auto& s : curNode->m_spheres) {
                potiential_spheres.push_back(s);
            }
        }
    }

    return numIntersections;
}
