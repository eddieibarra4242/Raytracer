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

#include "../Ray.h"
#include "../shapes/Sphere.h"

class AABB {
public:
  AABB() = default;
  AABB(glm::vec3 corner1, glm::vec3 corner2)
    : m_min(glm::min(corner1, corner2)), m_max(glm::max(corner1, corner2)) {}

  [[nodiscard]] bool intersect(const Ray &ray) const;

  void fit(const Sphere &s);

  [[nodiscard]] constexpr glm::vec3 min() const { return m_min; }
  [[nodiscard]] constexpr glm::vec3 max() const { return m_max; }

private:
  glm::vec3 m_min;
  glm::vec3 m_max;
};
