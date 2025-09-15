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
#include <vector>

#include "sas/BVH.hpp"
#include "shapes/Shape.hpp"

struct Intersection {
  bool has_hit;
  bool front_face;
  float distance;
  glm::vec3 intersection_point;
  glm::vec3 normal;
  std::shared_ptr<Shape> shape;
};

class Scene {
public:
  Scene() = default;

  inline void add_shape(const std::shared_ptr<Sphere> &sphere) {
    bvh.add(sphere);
  }

  inline void process() { bvh.process(); }

  [[nodiscard]] constexpr size_t getNumIntersections() const {
    return m_numIntersections;
  }

  [[nodiscard]] Intersection hit(std::vector<std::shared_ptr<Sphere>> &spheres,
                                 const Ray &ray);

private:
  BVH bvh;
  size_t m_numIntersections = 0;
};
