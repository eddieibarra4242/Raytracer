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

#include "Emissive.h"

#include "../Scene.h"
#include "../vec_utilities.h"

static constexpr glm::vec3 ZERO { 0, 0, 0 };

Scatter Emissive::scatter([[maybe_unused]] const Ray &incident, [[maybe_unused]] const Intersection &intersection) const {
    return { true, true, m_color, Ray{ ZERO, ZERO } };
}
