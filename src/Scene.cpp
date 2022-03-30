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

Intersection Scene::hit(const Ray &ray) const {
    float min_t = std::numeric_limits<float>::max();
    size_t index = m_shapes.size();

    for(size_t i = 0; i < m_shapes.size(); i++) {
        float t = m_shapes[i]->intersect(ray);

        if(t >= 0 && t < min_t) {
            min_t = t;
            index = i;
        }
    }

    if(index < m_shapes.size()) {
        return Intersection { true, min_t, m_shapes[index] };
    }

    return Intersection { false, -1.0f, std::shared_ptr<Shape>{ } };
}
