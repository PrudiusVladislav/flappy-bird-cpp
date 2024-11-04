//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#include "SfmlRenderer.h"
#include "Bird.h"
#include "Obstacle.h"
#include "Event.h"
#include "Color.h"


#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Event.hpp"


SfmlRenderer::SfmlRenderer(const Vector& size, Clock clock, int fps, const std::string& title) :
    IRenderer(size),
    window(sf::VideoMode(size.x, size.y), title), clock(clock)
{
    window.setFramerateLimit(fps);
}

void SfmlRenderer::clear() {
    window.clear();
}

void SfmlRenderer::renderBird(const Bird& bird) {
    sf::CircleShape circle(bird.getRadius());
    circle.setPosition(bird.getPosition().x, bird.getPosition().y);
    const Color& color = bird.getColor();
    circle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    window.draw(circle);
}

void SfmlRenderer::renderPipe(const Pipe& pipe) {
    sf::RectangleShape rectangle(sf::Vector2f(pipe.getSize().x, pipe.getSize().y));
    const Vector& position = pipe.getPosition();
    rectangle.setPosition(position.x, position.y);
    const Color& color = pipe.getFillColor();
    rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    window.draw(rectangle);
}

void SfmlRenderer::render() {
    window.display();
}

bool SfmlRenderer::pollEvent(Event& event) {
    sf::Event sfEvent;
    if (window.pollEvent(sfEvent)) {
        event = convertSfEventToCustomEvent(sfEvent);
        return true;
    }
    return false;
}

Event SfmlRenderer::convertSfEventToCustomEvent(const sf::Event& sfEvent) {
    Event event;
    switch (sfEvent.type) {
        case sf::Event::Closed:
            event.type = EventType::Closed;
        break;
        case sf::Event::KeyPressed:
            event.type = EventType::KeyPressed;
            event.key.code = static_cast<Key>(sfEvent.key.code);
        break;
        case sf::Event::KeyReleased:
            event.type = EventType::KeyReleased;
            event.key.code = static_cast<Key>(sfEvent.key.code);
        break;
        case sf::Event::MouseMoved:
            event.type = EventType::MouseMoved;
            event.mouseMove.x = sfEvent.mouseMove.x;
            event.mouseMove.y = sfEvent.mouseMove.y;
        break;
        case sf::Event::MouseWheelScrolled:
            event.type = EventType::MouseWheelScrolled;
            event.mouseWheelScroll.delta = sfEvent.mouseWheelScroll.delta;
            event.mouseWheelScroll.x = sfEvent.mouseWheelScroll.x;
            event.mouseWheelScroll.y = sfEvent.mouseWheelScroll.y;
        break;
        default:
            event.type = EventType::Count;
        break;
    }
    return event;
}
