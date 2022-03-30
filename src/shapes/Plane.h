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

class Plane : public Shape {
public:
    Plane(const glm::vec3& normal, const glm::vec3& point): m_normal{ glm::normalize(normal) }, m_point{ point } { }

    float intersect(const Ray &ray) override;
private:
    glm::vec3 m_normal;
    glm::vec3 m_point; //TODO: change to a scalar representation.
                       //float m_distance;
};
