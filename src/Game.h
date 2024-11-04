//
// Created by Vladyslav Prudius  on 04.11.2024.
//

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Bird.h"
#include "Obstacle.h"
#include "IRenderer.h"
#include "IGameStorage.h"

#include "Clock.h"

const float OBSTACLE_SPAWN_TIME_S = 2.0f;

enum GameState {
    WAITING_TO_START,
    PLAYING,
    GAME_OVER
};

class Game {
public:
    Game(IRenderer& renderer, IGameStorage& storage);

    void run();

private:
    void processInput();
    void update();
    void render();
    void createObstacle();
    bool checkCollision();
    void saveScore();

    IRenderer& renderer;
    IGameStorage& storage;
    Bird bird;
    std::vector<Obstacle> obstacles;
    float birdVelocity;
    Clock clock;
    float obstacleSpawnTimeS = OBSTACLE_SPAWN_TIME_S;
    GameState gameState;
    int score;
};



#endif //GAME_H
