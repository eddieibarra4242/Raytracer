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

#include "Scene.h"

#include "vec_utilities.h"

Intersection Scene::hit(std::vector<std::shared_ptr<Sphere>>& spheres, const Ray &ray) {
    m_numIntersections = bvh.coarseIntersect(spheres, ray);

    if(spheres.empty()) {
        return Intersection { false, false, -1.0f, ZERO_VECTOR, ZERO_VECTOR, std::shared_ptr<Shape>{ } };
    }

    float min_t = std::numeric_limits<float>::max();
    size_t index = spheres.size();

    for(size_t i = 0; i < spheres.size(); i++) {
        float t = spheres[i]->intersect(ray);
        m_numIntersections++;

        if(t >= T_EPSILON && t < min_t) {
            min_t = t;
            index = i;
        }
    }

    if(index < spheres.size()) {
        glm::vec3 intersection_point = ray.origin + (ray.direction * min_t);
        glm::vec3 normal = spheres[index]->normal(intersection_point);
        bool front_face = dot(ray.direction, normal) <= 0;
        return Intersection { true, front_face, min_t, intersection_point, (front_face ? 1.0f : -1.0f) * normal, spheres[index] };
    }

    return Intersection { false, false, -1.0f, ZERO_VECTOR, ZERO_VECTOR, std::shared_ptr<Shape>{ } };
}
