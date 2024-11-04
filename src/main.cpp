#include "FileGameStorage.h"
#include "Game.h"
#include "SfmlRenderer.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FPS = 60;

int main() {
    Clock clock = Clock();
    SfmlRenderer renderer({WINDOW_WIDTH, WINDOW_HEIGHT}, clock, FPS, "Flappy Bird");
    FileGameStorage storage("../game_data.txt");

    Game game(renderer, storage);
    game.run();

    return 0;
}