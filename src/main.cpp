#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FPS = 60;
const float BIRD_RADIUS = 20.0f;
const float GRAVITY = 0.8f;
const float JUMP_STRENGTH = -10.0f;
const float OBSTACLE_WIDTH = 50.0f;
const float OBSTACLE_SPEED = 5.0f;
const float OBSTACLE_GAP = 200.0f;

struct Obstacle {
    sf::RectangleShape top;
    sf::RectangleShape bottom;
};

void createObstacle(std::vector<Obstacle>& obstacles) {
    float gapPosition = static_cast<float>(std::rand() % (WINDOW_HEIGHT - static_cast<int>(OBSTACLE_GAP)));
    Obstacle obstacle;
    obstacle.top.setSize(sf::Vector2f(OBSTACLE_WIDTH, gapPosition));
    obstacle.top.setPosition(WINDOW_WIDTH, 0);
    obstacle.top.setFillColor(sf::Color::Green);

    obstacle.bottom.setSize(sf::Vector2f(OBSTACLE_WIDTH, WINDOW_HEIGHT - gapPosition - OBSTACLE_GAP));
    obstacle.bottom.setPosition(WINDOW_WIDTH, gapPosition + OBSTACLE_GAP);
    obstacle.bottom.setFillColor(sf::Color::Green);

    obstacles.push_back(obstacle);
}

bool checkCollision(const sf::CircleShape& bird, const Obstacle& obstacle) {
    return bird.getGlobalBounds().intersects(obstacle.top.getGlobalBounds()) ||
           bird.getGlobalBounds().intersects(obstacle.bottom.getGlobalBounds());
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird");
    window.setFramerateLimit(FPS);

    sf::CircleShape bird(BIRD_RADIUS);
    bird.setFillColor(sf::Color::Yellow);
    bird.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);

    float birdVelocity = 0.0f;
    std::vector<Obstacle> obstacles;
    sf::Clock clock;
    sf::Time obstacleSpawnTime = sf::seconds(2.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                birdVelocity = JUMP_STRENGTH;
            }
        }

        birdVelocity += GRAVITY;
        bird.move(0, birdVelocity);

        if (clock.getElapsedTime() > obstacleSpawnTime) {
            createObstacle(obstacles);
            clock.restart();
        }

        for (auto& obstacle : obstacles) {
            obstacle.top.move(-OBSTACLE_SPEED, 0);
            obstacle.bottom.move(-OBSTACLE_SPEED, 0);
        }

        obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle& obstacle) {
            return obstacle.top.getPosition().x + OBSTACLE_WIDTH < 0;
        }), obstacles.end());

        window.clear(sf::Color::Black);

        window.draw(bird);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle.top);
            window.draw(obstacle.bottom);
        }

        // Check for collisions
        for (const auto& obstacle : obstacles) {
            if (checkCollision(bird, obstacle)) {
                // Collision detected, handle it (e.g., end the game, restart, etc.)
                window.close();
            }
        }

        window.display();
    }

    return 0;
}