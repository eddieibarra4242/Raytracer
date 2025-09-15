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

#include "../Ray.hpp"
#include <glm/glm.hpp>

struct Intersection;

struct Scatter {
  bool absorbed;
  bool emissive = false;
  glm::vec3 attenuation;
  Ray scattered_ray;
};

class Material {
public:
  virtual ~Material() = default;
  [[nodiscard]] virtual Scatter
  scatter(const Ray &incident, const Intersection &intersection) const = 0;
};
