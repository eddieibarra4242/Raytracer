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

#include "Dielectric.h"
#include "../Scene.h"

#include "../vec_utilities.h"

constexpr float reflectance(float cos, float refraction_index) {
    auto r0 = (1.0 - static_cast<double>(refraction_index)) / (1.0 + static_cast<double>(refraction_index));
    r0 = r0 * r0;
    return static_cast<float>(r0 + (1.0 - r0) * std::pow(1 - cos, 5));
}

Scatter Dielectric::scatter(const Ray &incident, const Intersection &intersection) const {
    float ir = intersection.front_face ? (1.0f / m_refraction_index) : m_refraction_index;

    float cos_theta = dot(-incident.direction, intersection.normal);
    float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

    glm::vec3 direction { };

    if(ir * sin_theta > 1.0f || reflectance(cos_theta, ir) > random_float()) {
        direction = reflect(incident.direction, intersection.normal);
    } else {
        direction = refract(incident.direction, intersection.normal, ir, cos_theta);
    }

    return {false, glm::vec3(1), Ray{ intersection.intersection_point, direction }};
}
