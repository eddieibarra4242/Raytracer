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

int main()
{
    Window window(1280, 720, "Raytracer");
    Bitmap frame {1280, 720};

    for(uint32_t y = 0; y < frame.height(); y++) {
        for(uint32_t x = 0; x < frame.width(); x++) {
            double ratio = ((static_cast<double>(x) / static_cast<double>(frame.width())) + (static_cast<double>(y) / static_cast<double>(frame.height()))) / 2;
            frame.draw(x, y, {static_cast<uint8_t>(x), static_cast<uint8_t>(y), static_cast<uint8_t>(ratio * 255), 0});
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
