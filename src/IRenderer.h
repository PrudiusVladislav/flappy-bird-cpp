//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef IRENDERER_H
#define IRENDERER_H

#include "Bird.h"
#include "Event.h"

class IRenderer {
public:
    IRenderer(const Vector& size) : windowSize(size) {}
    virtual void clear() = 0;
    virtual void renderBird(const Bird& bird) = 0;
    virtual void renderPipe(const Pipe& pipe) = 0;
    virtual void render() = 0;
    virtual bool pollEvent(Event& event) = 0;

    Vector getWindowSize() const {
        return windowSize;
    }
protected:
    Vector windowSize;
};
#endif //IRENDERER_H
