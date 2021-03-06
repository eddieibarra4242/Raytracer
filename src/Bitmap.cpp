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

#include "Bitmap.h"

Bitmap::Bitmap(uint32_t width, uint32_t height) : m_pixels{ new Color[width * height] }, m_width{ width }, m_height{ height }, m_has_changed{ true }
{
    glGenTextures(1, &m_texture_id);
}

Bitmap::~Bitmap() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_texture_id);
}

void Bitmap::update() {
    if(!m_has_changed) {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<int>(m_width), static_cast<int>(m_height), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixels.get());

    m_has_changed = false;
}

void Bitmap::renderWithGL() {
    update();
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glBegin(GL_QUADS);

    glTexCoord2d(0, 1);
    glVertex2i(-1, -1);
    glTexCoord2d(1, 1);
    glVertex2i( 1, -1);
    glTexCoord2d(1, 0);
    glVertex2i( 1,  1);
    glTexCoord2d(0, 0);
    glVertex2i(-1,  1);

    glEnd();
}