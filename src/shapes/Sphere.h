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

#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere(const glm::vec3& position, float radius) : m_position{ position }, m_radius{ radius } { }

    float intersect(const Ray& ray) override;
private:
    glm::vec3 m_position;
    float m_radius;
};