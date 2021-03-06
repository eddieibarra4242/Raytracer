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

#include <random>
#include <glm/glm.hpp>

constexpr float EPSILON = 1e-6f;
constexpr float T_EPSILON = 1e-2f;

constexpr glm::vec3 ZERO_VECTOR{0, 0, 0};

//glm::dot is too slow to for ray-shape intersections
constexpr float dot(const glm::vec3& v1, const glm::vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

constexpr float distance_sq(const glm::vec3& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

constexpr glm::vec3 normalize(const glm::vec3& v) {
    float length = sqrtf(distance_sq(v));
    return glm::vec3{v.x / length, v.y / length, v.z / length};
}

constexpr glm::vec3 reflect(const glm::vec3& vector, const glm::vec3& normal) {
    return vector - 2 * dot(vector, normal) * normal;
}

constexpr glm::vec3 refract(const glm::vec3& incident, const glm::vec3& normal, float refraction_index) {
    auto cos_theta = dot(-incident, normal); //since both are normalized, range should be [-1, 1].
    glm::vec3 refract_perpendicular = refraction_index * (incident + cos_theta * normal);
    glm::vec3 refract_parallel = -sqrtf(fabsf(1.0f - distance_sq(refract_perpendicular))) * normal;
    return normalize(refract_perpendicular + refract_parallel);
}

constexpr glm::vec3 refract(const glm::vec3& incident, const glm::vec3& normal, float refraction_index, float cos_theta) {
    glm::vec3 refract_perpendicular = refraction_index * (incident + cos_theta * normal);
    glm::vec3 refract_parallel = -sqrtf(fabsf(1.0f - distance_sq(refract_perpendicular))) * normal;
    return normalize(refract_perpendicular + refract_parallel);
}

constexpr uint32_t min(uint32_t a, uint32_t b) {
    return a < b ? a : b;
}

inline float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float random_float(float min, float max) {
    return (random_float() * (max - min)) + min;
}

inline glm::vec3 random_color() {
    return glm::vec3 {random_float(), random_float(), random_float()};
}

inline glm::vec3 random_color(float min, float max) {
    return glm::vec3 {random_float(min, max), random_float(min, max), random_float(min, max)};
}

inline glm::vec3 random_normalized_vector() {
    return normalize(glm::vec3 {random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f)});
}

inline glm::vec3 random_from_hemisphere(const glm::vec3& normal) {
    glm::vec3 vec = random_normalized_vector();

    if(dot(vec, normal) < 0) {
        return vec * -1.0f;
    }

    return vec;
}