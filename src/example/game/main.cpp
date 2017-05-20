#include <SDL.h>
#include <SDL_main.h>

#include "deps/Game.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // SDL_WINDOW_FULLSCREEN
    // SDL_WINDOW_FULLSCREEN_DESKTOP
    if(TheGame::Instance()->init("Ch 1", 100, 100, 640, 480, SDL_WINDOW_BORDERLESS)) {

        while(TheGame::Instance()->running()) {
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            SDL_Delay(10);
        }

    } else {
        cout << SDL_GetError() << "\n";
    }

    TheGame::Instance()->clean();

    return 0;
}
