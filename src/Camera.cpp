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
#include "vec_utilities.h"

constexpr float VIEW_PORT_HEIGHT = 2.2f;

Camera::Camera(const glm::vec3 &position, const glm::vec3 &forward,
               float aspect_ratio, float fov, float aperture,
               float focal_length)
  : m_position{position}, m_forward{normalize(forward)},
    m_lens_radius{aperture / 2.0f}, m_focal_length{focal_length} {

  float view_port_height = 2.0f * VIEW_PORT_HEIGHT * tanf(fov / 2.0f);
  float view_port_width = view_port_height * aspect_ratio;

  static constexpr auto UP = glm::vec3(0, 1, 0);
  m_right = normalize(glm::cross(UP, m_forward));
  m_up = normalize(glm::cross(m_forward, m_right));

  m_horizontal = m_right * view_port_width;
  m_vertical = m_up * view_port_height;
  m_top_left = forward - (m_horizontal * 0.5f) + (m_vertical * 0.5f);
}

Ray Camera::to_ray(float x, float y) {
  glm::vec3 offset =
    (m_right * random_float(-1.0f, 1.0f) + m_up * random_float(-1.0f, 1.0f)) *
    m_lens_radius;
  glm::vec3 origin = m_position + offset;
  glm::vec3 prefect_direction =
    normalize(m_top_left + x * m_horizontal - y * m_vertical);
  return Ray{origin, normalize(prefect_direction * m_focal_length - offset)};
}
