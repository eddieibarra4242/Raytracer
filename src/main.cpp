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

#include "shapes/Shape.h"
#include "shapes/Sphere.h"
#include "shapes/Plane.h"

#include <glm/glm.hpp>

int main()
{
    Window window(1280, 720, "Raytracer");
    Bitmap frame (1280, 720);

    auto aspect_ratio = static_cast<float>(frame.width()) / static_cast<float>(frame.height());

    Camera camera{glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), aspect_ratio, 1.0f};

    std::unique_ptr<Shape> sphere {new Sphere{glm::vec3(0, 0, 2), 1}};
    std::unique_ptr<Shape> plane {new Plane{glm::vec3(0, 1, 0), glm::vec3(0, -1, 0)}};

    for(uint32_t y = 0; y < frame.height(); y++) {
        for(uint32_t x = 0; x < frame.width(); x++) {
            auto u = static_cast<float>(x) / static_cast<float>(frame.width() - 1);
            auto v = static_cast<float>(y) / static_cast<float>(frame.height() - 1);
            Ray r = camera.to_ray(u, v);

            glm::vec3 color = Ray::sky_color(r) * 255.0f;
            Color pixel_color{static_cast<uint8_t>(color.r), static_cast<uint8_t>(color.g), static_cast<uint8_t>(color.b), 255};

            if(plane->intersect(r) >= 0) {
                pixel_color = {0, 255, 0, 255};
            }

            if(sphere->intersect(r) >= 0) {
                pixel_color = {255, 0, 0, 255};
            }

            frame.draw(x, y, pixel_color);
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
