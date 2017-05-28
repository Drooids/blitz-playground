#include <SDL.h>
#include <SDL_main.h>

#include "deps/Game.h"
#include <iostream>
#include <stdint.h>
#include <inttypes.h>

using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char *argv[])
{
	uint32_t frameStart, frameTime;

    // SDL_WINDOW_FULLSCREEN
    // SDL_WINDOW_FULLSCREEN_DESKTOP
    // SDL_WINDOW_BORDERLESS
    if(TheGame::Instance()->init("Ch 1", 100, 100, 640, 480, 0)) {

        while(TheGame::Instance()->running()) {

			frameStart = SDL_GetTicks();

            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			/*
				First we get the time at the start of our loop and store it in frameStart. For this we
				use SDL_GetTicks which returns the amount of milliseconds since we called SDL_
				Init. We then run our game loop and store how long it took to run by subtracting
				the time our frame started from the current time. If it is less than the time we want a
				frame to take, we call SDL_Delay and make our loop wait for the amount of time we
				want it to, subtracting how long the loop already took to complete.
			*/
			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
        }

    } else {
        cout << SDL_GetError() << "\n";
    }

    TheGame::Instance()->clean();

    return 0;
}
