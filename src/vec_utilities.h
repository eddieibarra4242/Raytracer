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

#pragma once

#include <glm/glm.hpp>

constexpr float EPSILON = 1e-6f;

//glm::dot is too slow to for ray-shape intersections
constexpr float dot(const glm::vec3& v1, const glm::vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

constexpr float distance_sq(const glm::vec3& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}