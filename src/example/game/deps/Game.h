#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <stdio.h>
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>

#include "TextureManager.h"

class Game
{
public:
    // Game();
    ~Game();

    static Game* Instance();

    /*
        Flags:
            SDL_WINDOW_FULLSCREEN Make the window full-screen
            SDL_WINDOW_OPENGL Window can be used with as an OpenGL context
            SDL_WINDOW_SHOWN The window is visible
            SDL_WINDOW_HIDDEN Hide the window
            SDL_WINDOW_BORDERLESS No border on the window
            SDL_WINDOW_RESIZABLE Enable resizing of the window
            SDL_WINDOW_MINIMIZED Minimize the window
            SDL_WINDOW_MAXIMIZED Maximize the window
            SDL_WINDOW_INPUT_GRABBED Window has grabbed input focus
            SDL_WINDOW_INPUT_FOCUS Window has input focus
            SDL_WINDOW_MOUSE_FOCUS Window has mouse focus
            SDL_WINDOW_FOREIGN The window was not created using SDL
    */

    bool init(
        const char* title, int xpos, int ypos,
        int width, int height, int flags
    );

    void render();
    void update();
    void handleEvents();
    void clean();

    bool running();

private:

    // SDL

    SDL_Window* m_pWindow = NULL;
    SDL_Renderer* m_pRenderer = NULL;

    // SDL_image

    // Other

    bool m_bRunning;
	int m_currentFrame;
};

typedef Game TheGame;

#endif
