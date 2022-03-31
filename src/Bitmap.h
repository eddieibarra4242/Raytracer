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

#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>

constexpr float GAMMA = 2.2f;

struct Color {
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;

    constexpr Color() = default;
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha } {}

    static constexpr Color to_color(const glm::vec3& color) {
        glm::vec3 ranged_color = glm::clamp(glm::pow(color, glm::vec3(1.0f / GAMMA)), 0.0f, 1.0f) * 255.0f;
        return Color{static_cast<uint8_t>(ranged_color.r), static_cast<uint8_t>(ranged_color.g), static_cast<uint8_t>(ranged_color.b), 255};
    }
};

class Bitmap {
public:
    Bitmap(uint32_t width, uint32_t height);
    ~Bitmap();

    constexpr void draw(uint32_t x, uint32_t y, Color value) {
        m_has_changed = true;
        get_wrapped(x, y) = value;
    }

    [[nodiscard]] constexpr Color read(uint32_t x, uint32_t y) const { return get_wrapped(x, y); }

    [[nodiscard]] constexpr uint32_t width() const { return m_width; }
    [[nodiscard]] constexpr uint32_t height() const { return m_height; }

    void renderWithGL();
private:
    std::unique_ptr<Color> m_pixels;
    uint32_t m_width;
    uint32_t m_height;

    bool m_has_changed;
    GLuint m_texture_id{};

    [[nodiscard]] constexpr Color& get_wrapped(uint32_t x, uint32_t y) {
        uint32_t x_wrapped = x % m_width;
        uint32_t y_wrapped = y % m_height;
        return m_pixels.get()[x_wrapped + y_wrapped * m_width];
    }

    [[nodiscard]] constexpr const Color& get_wrapped(uint32_t x, uint32_t y) const {
        uint32_t x_wrapped = x % m_width;
        uint32_t y_wrapped = y % m_height;
        return m_pixels.get()[x_wrapped + y_wrapped * m_width];
    }

    void update();
};
