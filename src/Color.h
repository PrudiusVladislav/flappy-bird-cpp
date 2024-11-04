//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef COLOR_H
#define COLOR_H
#include <cstdint>

class Color {
public:
    Color() : r(0), g(0), b(0), a(255) {}
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) :
        r(red), g(green), b(blue), a(alpha) {}

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Transparent;

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

#endif //COLOR_H
