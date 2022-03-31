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

#include "Plane.h"
#include "../vec_utilities.h"

float Plane::intersect(const Ray &ray) {
    float denominator = dot(m_normal, ray.direction);

    if (denominator > EPSILON || denominator < -EPSILON) {
        glm::vec3 to_point = m_point - ray.origin;
        return dot(to_point, m_normal) / denominator;
    }

    return -1;
}

glm::vec3 Plane::normal(const glm::vec3 &point) {
    return m_normal;
}
