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

#include "materials/Lambertian.h"
#include "materials/Metal.h"
#include "materials/Dielectric.h"

constexpr glm::vec3 CAMERA_POSITION {-13, 2, 3};
constexpr glm::vec3 CAMERA_FORWARD = glm::vec3{0, 0, 0} - CAMERA_POSITION;

constexpr uint32_t DEFAULT_QUAD_SIZE = 100;

constexpr float PI = 3.14159265358979323846264338327950288419f;

glm::vec3 get_color(const Scene& scene, const Ray& ray, uint32_t bounce_budget) {
    if(bounce_budget == 0) {
        return ZERO_VECTOR;
    }

    Intersection hit = scene.hit(ray);

    if(hit.has_hit) {
        Scatter scatter = hit.shape->material()->scatter(ray, hit);

        if(scatter.absorbed) {
            return ZERO_VECTOR;
        }

        return scatter.attenuation * get_color(scene, scatter.scattered_ray, bounce_budget - 1);
    }

    return Ray::sky_color(ray);
}

void split_image(std::queue<Quad>& queue, const Bitmap& image, uint32_t quad_size) {
    uint32_t num_columns = image.width() / quad_size + 1;
    uint32_t num_rows = image.height() / quad_size + 1;

    for(uint32_t y = 0; y < num_rows; y++) {
        for(uint32_t x = 0; x < num_columns; x++) {
            queue.emplace(Quad::vec2i{ x * quad_size, y * quad_size }, Quad::vec2i{ min((x + 1) * quad_size, image.width()), min((y + 1) * quad_size, image.height()) });
        }
    }
}

Renderer::Renderer(uint32_t width, uint32_t height, size_t thread_count) :
    m_image(width, height),
    m_camera(CAMERA_POSITION, CAMERA_FORWARD, static_cast<float>(width) / static_cast<float>(height), PI / 2.0f, 0.1f, 10.0f) {

    auto ground_material = std::make_shared<Lambertian>(glm::vec3(0.5));
    m_scene.add_shape(std::make_shared<Sphere>(glm::vec3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            glm::vec3 center(static_cast<float>(a) + 0.9f * random_float(), 0.2f, static_cast<float>(b) + 0.9f * random_float());

            if (glm::length(center - glm::vec3(4, 0.2f, 0)) > 0.9f) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8f) {
                    // diffuse
                    auto albedo = random_color() * random_color();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    m_scene.add_shape(std::make_shared<Sphere>(center, 0.2f, sphere_material));
                } else if (choose_mat < 0.95f) {
                    // metal
                    auto albedo = random_color(0.5f, 1);
                    auto fuzz = random_float(0, 0.5f);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    m_scene.add_shape(std::make_shared<Sphere>(center, 0.2f, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5f);
                    m_scene.add_shape(std::make_shared<Sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5f);
    m_scene.add_shape(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1.0f, material1));

    auto material2 = std::make_shared<Lambertian>(glm::vec3 (0.4f, 0.2f, 0.1f));
    m_scene.add_shape(std::make_shared<Sphere>(glm::vec3(4, 1, 0), 1.0f, material2));

    auto material3 = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);
    m_scene.add_shape(std::make_shared<Sphere>(glm::vec3(-4, 1, 0), 1.0f, material3));

    m_rendering_threads.reserve(thread_count);
    split_image(m_work_queue, m_image, DEFAULT_QUAD_SIZE);
}

void Renderer::start_render() {
    auto render_func = [this]() {
        while(true) {
            Quad q { ZERO_VECTOR, ZERO_VECTOR };

            {
                std::lock_guard<std::mutex> lock{m_queue_mutex};

                if(m_work_queue.empty()) {
                    return;
                }

                q = m_work_queue.front();
                m_work_queue.pop();
            }

            for (uint32_t y = q.m_min.y; y < q.m_max.y; y++) {
                for (uint32_t x = q.m_min.x; x < q.m_max.x; x++) {
                    glm::vec3 color{0, 0, 0};

                    for (uint32_t sample = 0; sample < samples; sample++) {
                        if (m_should_stop) {
                            return;
                        }

                        auto u = (static_cast<float>(x) + random_float()) / static_cast<float>(m_image.width() - 1);
                        auto v = (static_cast<float>(y) + random_float()) / static_cast<float>(m_image.height() - 1);
                        Ray r = m_camera.to_ray(u, v);
                        color += get_color(m_scene, r, max_bounces);
                    }

                    color *= (1.0f / static_cast<float>(samples));
                    m_image.draw(x, y, Color::to_color(color));
                }
            }
        }
    };

    for(size_t i = 0; i < m_rendering_threads.capacity(); i++) {
        m_rendering_threads.emplace_back(render_func);
    }
}

void Renderer::stop_render() {
    if(m_rendering_threads.empty()) {
        return;
    }

    m_should_stop = true;
    for(auto& thread : m_rendering_threads) {
        thread.join();
    }
}

void Renderer::present() {
    m_image.renderWithGL();
}