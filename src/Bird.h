//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef BIRD_H
#define BIRD_H
#include <iostream>
#include <ostream>
#include <__algorithm/clamp.h>

#include "Obstacle.h"
#include "Vector.h"

const float BIRD_RADIUS = 20.0f;
const float GRAVITY = 0.8f;
const float JUMP_STRENGTH = -10.0f;

class Bird {
public:
    Bird(const Vector& position, const Color& color) :
        position(position), velocity(0.0f, 0.0f), color(color) {
    }

    bool checkCollision(const Obstacle& obstacle) const {
        return checkCircleRectCollision(position, radius, obstacle.top.getPosition(), obstacle.top.getSize()) ||
               checkCircleRectCollision(position, radius, obstacle.bottom.getPosition(), obstacle.bottom.getSize());
    }

    void update() {
        velocity.y += gravity;
        position.y += velocity.y;
    }
    void jump() {
        velocity.y = jumpStrength;
    }

    float getRadius() const {
        return radius;
    }

    Vector getPosition() const {
        return position;
    }

    Color getColor() const {
        return color;
    }
private:
    float radius = BIRD_RADIUS;
    Color color;
    Vector position;
    Vector velocity;
    float gravity = GRAVITY;
    float jumpStrength = JUMP_STRENGTH;

    bool checkCircleRectCollision(const Vector& circleCenter, float radius, const Vector& rectPos, const Vector& rectSize) const {
        float closestX = std::clamp(circleCenter.x, rectPos.x, rectPos.x + rectSize.x);
        float closestY = std::clamp(circleCenter.y, rectPos.y, rectPos.y + rectSize.y);

        float distanceX = circleCenter.x - closestX;
        float distanceY = circleCenter.y - closestY;

        return (distanceX * distanceX + distanceY * distanceY) < (radius * radius);
    }
};



#endif //BIRD_H
