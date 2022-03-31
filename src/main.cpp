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

#include "Window.h"
#include "Bitmap.h"

#include "Ray.h"
#include "Camera.h"

#include "shapes/Sphere.h"
#include "shapes/Plane.h"
#include "Scene.h"

#include <glm/glm.hpp>

#include "vec_utilities.h"

int main()
{
    Window window(1280, 720, "Raytracer");
    Bitmap frame (1280, 720);

    auto aspect_ratio = static_cast<float>(frame.width()) / static_cast<float>(frame.height());

    uint32_t samples = 10;

    Camera camera{glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), aspect_ratio, 1.0f};

    Scene scene;
    scene.add_shape(std::make_shared<Sphere>(glm::vec3(0, 0, 2.0f), 1.0f));
    scene.add_shape(std::make_shared<Plane>(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0)));

    for(uint32_t y = 0; y < frame.height(); y++) {
        for(uint32_t x = 0; x < frame.width(); x++) {
            glm::vec3 color {0, 0, 0};

            for(uint32_t sample = 0; sample < samples; sample++) {
                auto u = (static_cast<float>(x) + random_float()) / static_cast<float>(frame.width() - 1);
                auto v = (static_cast<float>(y) + random_float()) / static_cast<float>(frame.height() - 1);
                Ray r = camera.to_ray(u, v);

                Intersection hit = scene.hit(r);

                if(hit.has_hit) {
                    color += glm::abs(hit.normal);
                } else {
                    color += Ray::sky_color(r);
                }
            }

            color *= (1.0f / static_cast<float>(samples));
            frame.draw(x, y, Color::to_color(color));
        }
    }

    glClearColor(1, 0, 0, 1);

    while(!window.shouldClose()) {
        Window::poll();

        glClear(GL_COLOR_BUFFER_BIT);

        frame.renderWithGL();

        window.present();
    }
}
