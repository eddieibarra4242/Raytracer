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

struct Ray {
  glm::vec3 origin;
  glm::vec3 direction;

  static glm::vec3 sky_color([[maybe_unused]] const Ray &r) {
    // static constexpr auto blue = glm::vec3(0.5, 0.7, 1.0);
    // static constexpr auto white = glm::vec3{1.0, 1.0, 1.0};

    // auto t = 0.5f * (r.direction.y + 1.0f);
    // return white * (1.0f - t) + blue * t;

    return glm::vec3(0);
  }
};