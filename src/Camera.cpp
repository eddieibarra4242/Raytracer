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

#include "Camera.h"

constexpr float VIEW_PORT_HEIGHT = 2.0f;

Camera::Camera(const glm::vec3 &position, const glm::vec3 &forward, float aspect_ratio, float focal_length) :
    m_position{ position },
    m_forward{ glm::normalize(forward) } {
    static constexpr auto UP = glm::vec3 (0, 1, 0);
    m_right = glm::normalize(glm::cross(m_forward, UP));
    m_up = glm::normalize(glm::cross(m_right, m_forward));

    m_horizontal = m_right * VIEW_PORT_HEIGHT;
    m_vertical = m_up * VIEW_PORT_HEIGHT;
    m_top_left = (m_forward * focal_length) - (m_horizontal * 0.5f) + (m_vertical * 0.5f);
}

Ray Camera::to_ray(float x, float y) {
    return Ray{m_position, glm::normalize(m_top_left + x * m_horizontal - y * m_vertical)};
}
