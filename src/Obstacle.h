//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Color.h"
#include "Vector.h"

class Pipe {
public:
    Pipe () :
        position({0, 0}),
        size({0, 0}),
        color(Color::Green) {
    }

    Pipe(float x, float y, float width, float height, Color color) :
        position({x, y}),
        size({width, height}),
        color(color) {
    }

    Vector getPosition() const {
        return position;
    }

    Vector getSize() const {
        return size;
    }

    Color getFillColor() const {
        return color;
    }

    void setPosition(Vector position) {
        this->position = position;
    }

    void setSize(Vector size) {
        this->size = size;
    }

    void setFillColor(Color color) {
        this->color = color;
    }

    void move(float x, float y) {
        position.x += x;
        position.y += y;
    }
private:
    Vector position;
    Vector size;
    Color color;
};

const float OBSTACLE_WIDTH = 50.0f;
const float OBSTACLE_GAP = 200.0f;

struct Obstacle {
    Obstacle(float gapPosition, const Vector& windowSize, const Color& color): passed(false) {
        top.setSize({OBSTACLE_WIDTH, gapPosition});
        top.setPosition({windowSize.x, 0});
        top.setFillColor(color);

        bottom.setSize({OBSTACLE_WIDTH, windowSize.y - gapPosition - OBSTACLE_GAP});
        bottom.setPosition({windowSize.x, gapPosition + OBSTACLE_GAP});
        bottom.setFillColor(color);
    }

    Pipe top;
    Pipe bottom;
    bool passed;
};



#endif //OBSTACLE_H
