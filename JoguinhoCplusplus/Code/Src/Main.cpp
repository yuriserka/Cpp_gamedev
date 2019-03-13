#include "../Include/Game.h"

int main(int argc, char *args[]) {
    Game *game = new Game("joguinho", SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED, 800, 640,
                          false);
    game->run();

    delete game;

    return 0;
}