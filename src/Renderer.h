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

#include <vector>
#include <thread>

#include "Camera.h"
#include "Scene.h"
#include "Bitmap.h"

class Renderer {
public:
    Renderer(uint32_t width, uint32_t height) : Renderer(width, height, std::thread::hardware_concurrency()) { }
    explicit Renderer(uint32_t width, uint32_t height, size_t thread_count);

    void start_render();
    void stop_render();
    void present();
private:
    static constexpr uint32_t samples = 100;
    static constexpr uint32_t max_bounces = 16;

    bool m_should_stop = false;

    Bitmap m_image;

    Scene m_scene;
    Camera m_camera;

    std::unique_ptr<std::thread> m_rendering_thread;
};
