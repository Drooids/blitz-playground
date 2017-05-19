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
	// SDL_WINDOW_FULLSCREEN
	// SDL_WINDOW_FULLSCREEN_DESKTOP
    g_game->init("Ch 1", 100, 100, 640, 480, SDL_WINDOW_BORDERLESS);

    while(g_game->running()) {
        g_game->handleEvents();
        g_game->update();
        g_game->render();

		SDL_Delay(10);
    }

    g_game->clean();

    return 0;
}
