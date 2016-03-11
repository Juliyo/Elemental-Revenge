#include "../Headers/Game.hpp"

int main(int, char const**)
{
    Game *game = new Game();
    game->run();
    delete game;
}
