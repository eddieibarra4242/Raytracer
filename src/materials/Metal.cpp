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

#include "Metal.h"

#include "../Scene.h"
#include "../vec_utilities.h"

Scatter Metal::scatter(const Ray &incident, const Intersection &intersection) const {
    glm::vec3 reflected_direction = normalize(reflect(incident.direction, intersection.normal) + m_fuzz * random_normalized_vector());
    return { dot(reflected_direction, intersection.normal) <= 0, false, m_albedo, Ray{ intersection.intersection_point, reflected_direction } };
}
