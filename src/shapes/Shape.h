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

#include <memory>
#include <utility>

#include "../Ray.h"
#include "../materials/Material.h"

class Shape {
public:
  explicit Shape(std::shared_ptr<Material> material)
    : m_material{std::move(material)} {}
  virtual ~Shape() = default;

  [[nodiscard]] virtual glm::vec3 normal(const glm::vec3 &point) = 0;
  [[nodiscard]] virtual float intersect(const Ray &ray) = 0;

  [[nodiscard]] inline std::shared_ptr<Material> material() const {
    return m_material;
  }

private:
  std::shared_ptr<Material> m_material;
};