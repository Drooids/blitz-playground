#include <stdio.h>
#include <SDL.h>
#include <SDL_main.h>

#include "deps/Game.h"
#include <iostream>
using namespace std;

Game* g_game;

int main(int argc, char *argv[])
{
    g_game = new Game();
    g_game->init("Ch 1", 100, 100, 640, 480, SDL_WINDOW_FULLSCREEN);

    while(g_game->running()) {
        g_game->handleEvents();
        g_game->update();
        g_game->render();
    }

    g_game->clean();

    return 0;
}
