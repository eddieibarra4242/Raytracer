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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
  Window(uint32_t width, uint32_t height, const char *title);
  ~Window();

  [[nodiscard]] bool shouldClose() const;
  void present() const;
  static void poll();

  [[nodiscard]] constexpr uint32_t width() const { return m_width; }
  [[nodiscard]] constexpr uint32_t height() const { return m_height; }

private:
  GLFWwindow *m_window;
  uint32_t m_width;
  uint32_t m_height;
};
