//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#include "Game.h"

#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


const float OBSTACLE_SPEED = 5.0f;

Game::Game(IRenderer& renderer, IGameStorage& storage)
    : renderer(renderer),
      storage(storage),
      bird({renderer.getWindowSize().x / 4, renderer.getWindowSize().y / 2}, Color::Yellow),
      birdVelocity(0.0f),
      isGameOver(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::run() {
    while (!isGameOver) {
        processInput();
        update();
        render();
    }
    saveScore();
}

void Game::processInput() {
    Event event;
    while (renderer.pollEvent(event)) {
        if (event.type == EventType::Closed)
            isGameOver = true;
        if (event.type == EventType::KeyPressed && event.key.code == Key::Space) {
            bird.jump();
        }
    }
}

void Game::update() {
    bird.update();

    if (clock.getElapsedTimeS() > obstacleSpawnTimeS) {
        createObstacle();
        clock.restart();
    }

    for (auto& obstacle : obstacles) {
        obstacle.top.move(-OBSTACLE_SPEED, 0);
        obstacle.bottom.move(-OBSTACLE_SPEED, 0);
    }

    // obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle& obstacle) {
    //     return obstacle.top.getPosition().x + OBSTACLE_WIDTH < 0;
    // }), obstacles.end());

    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [this](Obstacle& obstacle) {
        if (obstacle.top.getPosition().x + OBSTACLE_WIDTH < bird.getPosition().x && !obstacle.passed) {
            score++;
            obstacle.passed = true;
        }
        return obstacle.top.getPosition().x + OBSTACLE_WIDTH < 0;
    }), obstacles.end());

    if (checkCollision()) {
        isGameOver = true;
    }
}

void Game::render() {
    renderer.clear();
    renderer.renderBird(bird);
    for (const auto& obstacle : obstacles) {
        renderer.renderPipe(obstacle.top);
        renderer.renderPipe(obstacle.bottom);
    }
    renderer.render();
}

void Game::createObstacle() {
    const Vector& windowSize = renderer.getWindowSize();
    float gapPosition = static_cast<float>(std::rand() % (static_cast<int>(windowSize.y) - static_cast<int>(OBSTACLE_GAP)));
    Obstacle obstacle(gapPosition, windowSize, Color::Green);
    obstacles.push_back(obstacle);
}

bool Game::checkCollision() {
    for (const auto& obstacle : obstacles) {
        if (bird.checkCollision(obstacle)) {
            return true;
        }
    }
    return false;
}

void Game::saveScore() {
    storage.save("score", std::to_string(score));
}