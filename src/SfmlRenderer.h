//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef SFMLRENDERER_H
#define SFMLRENDERER_H

#include "Clock.h"
#include "IRenderer.h"
#include "SFML/Graphics/RenderWindow.hpp"

class SfmlRenderer : public IRenderer {
public:
    SfmlRenderer(const Vector& size, Clock clock, int fps, const std::string& title);

    void clear() override;
    void renderBird(const Bird& bird) override;
    void renderPipe(const Pipe& pipe) override;
    void render() override;
    bool pollEvent(Event& event) override;

private:
    sf::RenderWindow window;
    Clock clock;
    Event convertSfEventToCustomEvent(const sf::Event& sfEvent);
};

#endif // SFMLRENDERER_H
