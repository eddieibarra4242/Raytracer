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

#include "../Ray.h"
#include "../shapes/Sphere.h"
#include "AABB.h"

struct Node {
  std::unique_ptr<Node> m_left;
  std::unique_ptr<Node> m_right;
  AABB m_boundingBox;
  std::vector<std::shared_ptr<Sphere>> m_spheres;
};

class BVH {
public:
  BVH() = default;

  void add(const std::shared_ptr<Sphere> &s);
  void process();

  size_t
  coarseIntersect(std::vector<std::shared_ptr<Sphere>> &potiential_spheres,
                  const Ray &ray) const;

private:
  static constexpr int MAX_SPHERES = 5;
  Node m_root;
};
