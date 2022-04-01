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

#include "Sphere.h"
#include "../vec_utilities.h"

float Sphere::intersect(const Ray &ray) {
    glm::vec3 to_center = ray.origin - m_position;

    auto a = 1.0f; // distance_sq(ray.direction) but ray.direction is normalized, so result is always 1.
    auto b = 2.0f * dot(to_center, ray.direction);
    auto c = distance_sq(to_center) - m_radius * m_radius;

    auto disc = b * b - 4.0f * a * c;

    if(disc < 0) {
        return -1;
    }

    auto t1 = (-b - sqrtf(disc)) / (2.0f * a);
    auto t2 = (-b + sqrtf(disc)) / (2.0f * a);

    if(t1 < T_EPSILON) {
        return t2;
    }

    return t1;
}

glm::vec3 Sphere::normal(const glm::vec3 &point) {
    return normalize(point - m_position);
}
