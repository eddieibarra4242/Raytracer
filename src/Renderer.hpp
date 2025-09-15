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

#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "Bitmap.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

struct Quad {
  using vec2i = glm::vec<2, uint32_t, glm::defaultp>;
  vec2i m_min;
  vec2i m_max;

  size_t m_sampleCount = 0;
  std::shared_ptr<glm::vec3[]> m_colorArr;

  Quad(const vec2i &min, const vec2i &max)
    : m_min(min), m_max(max),
      m_colorArr{std::make_shared<glm::vec3[]>(
        static_cast<size_t>((m_max.x - m_min.x) * (m_max.y - m_min.y)))} {}
};

class Renderer {
public:
  Renderer(uint32_t width, uint32_t height)
    : Renderer(width, height, std::thread::hardware_concurrency()) {}
  explicit Renderer(uint32_t width, uint32_t height, size_t thread_count);

  void start_render();
  void stop_render();
  void present();

  void reportAverage(double average);

private:
  static constexpr uint32_t samples = 8;
  static constexpr uint32_t max_bounces = 16;

  bool m_should_stop = false;

  Bitmap m_image;

  Scene m_scene;
  Camera m_camera;

  std::mutex m_queue_mutex;
  std::queue<Quad> m_work_queue;
  std::vector<std::thread> m_rendering_threads;

  std::mutex m_average_lock;
  double runningIntersectionsPerRayAverage = 0;
  double reportCount = 0;
};
