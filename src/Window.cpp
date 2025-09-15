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
#include "log.h"

#include <cstdlib>

Window::Window(uint32_t width, uint32_t height, const char *title)
  : m_width{width}, m_height{height} {
  if (!glfwInit()) {
    CRITICAL("glfw", "Failed to init GLFW");
  }

  glfwDefaultWindowHints();
  m_window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
                              title, nullptr, nullptr);

  const GLFWvidmode *vid_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwSetWindowPos(m_window, (vid_mode->width - static_cast<int>(width)) / 2,
                   (vid_mode->height - static_cast<int>(height)) / 2);

  glfwMakeContextCurrent(m_window);
  glfwShowWindow(m_window);
  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    CRITICAL("glew", "Failed to init GLEW");
  }

  glEnable(GL_TEXTURE_2D);
}

Window::~Window() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

bool Window::shouldClose() const { return glfwWindowShouldClose(m_window); }

void Window::present() const { glfwSwapBuffers(m_window); }

void Window::poll() { glfwPollEvents(); }
