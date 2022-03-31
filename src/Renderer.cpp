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

#include "Renderer.h"
#include "vec_utilities.h"

#include "shapes/Sphere.h"
#include "shapes/Plane.h"

constexpr glm::vec3 CAMERA_POSITION = ZERO_VECTOR;
constexpr glm::vec3 CAMERA_FORWARD {0, 0, 1};

glm::vec3 get_color(const Scene& scene, const Ray& ray, uint32_t bounce_budget) {
    if(bounce_budget == 0) {
        return ZERO_VECTOR;
    }

    Intersection hit = scene.hit(ray);

    if(hit.has_hit) {
        return glm::abs(hit.normal);
    }

    return Ray::sky_color(ray);
}

Renderer::Renderer(uint32_t width, uint32_t height, size_t thread_count) :
    m_image(width, height),
    m_camera(CAMERA_POSITION, CAMERA_FORWARD, static_cast<float>(width) / static_cast<float>(height), 1.0f),
    m_rendering_thread { } {
    m_scene.add_shape(std::make_shared<Sphere>(glm::vec3(0, 0, 2.0f), 1.0f));
    m_scene.add_shape(std::make_shared<Plane>(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0)));
}

void Renderer::start_render() {
    auto render_func = [this]() {
        for(uint32_t y = 0; y < m_image.height(); y++) {
            for(uint32_t x = 0; x < m_image.width(); x++) {
                glm::vec3 color {0, 0, 0};

                for(uint32_t sample = 0; sample < samples; sample++) {
                    auto u = (static_cast<float>(x) + random_float()) / static_cast<float>(m_image.width() - 1);
                    auto v = (static_cast<float>(y) + random_float()) / static_cast<float>(m_image.height() - 1);
                    Ray r = m_camera.to_ray(u, v);
                    color += get_color(m_scene, r, max_bounces);
                }

                color *= (1.0f / static_cast<float>(samples));
                m_image.draw(x, y, Color::to_color(color));
            }
        }
    };

    m_rendering_thread = std::make_unique<std::thread>(render_func);
}

void Renderer::stop_render() {
    if(m_rendering_thread == nullptr) {
        return;
    }

    m_rendering_thread->join();
}

void Renderer::present() {
    m_image.renderWithGL();
}