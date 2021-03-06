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
#include "Renderer.h"

#include <spdlog/spdlog.h>

int main()
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    static constexpr uint32_t WIDTH = 1280;
    static constexpr uint32_t HEIGHT = 720;

    Window window(WIDTH, HEIGHT, "Raytracer");
    Renderer renderer(WIDTH, HEIGHT);

    renderer.start_render();

    glClearColor(1, 0, 0, 1);

    while(!window.shouldClose()) {
        Window::poll();

        glClear(GL_COLOR_BUFFER_BIT);

        renderer.present();

        window.present();
    }

    renderer.stop_render();
}
