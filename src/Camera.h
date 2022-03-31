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

#include "Ray.h"

class Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec3& forward, float aspect_ratio, float fov, float aperture, float focal_length);

    Ray to_ray(float x, float y);
private:
    glm::vec3 m_position;

    glm::vec3 m_forward;
    glm::vec3 m_up;
    glm::vec3 m_right;

    glm::vec3 m_top_left;
    glm::vec3 m_horizontal;
    glm::vec3 m_vertical;

    float m_lens_radius;
    float m_focal_length;
};

