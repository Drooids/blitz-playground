#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include "GameObject.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"

#include <stdio.h>
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>

class Game
{
public:
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
	void draw();
	void update();
	void handleEvents();
	void clean();
	void quit() { m_bRunning = false; clean(); };

	bool running();

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	vector<GameObject*> m_gameObjects;

private:

	// Game();

	static Game* s_pInstance;

	// SDL

	SDL_Window* m_pWindow = NULL;
	SDL_Renderer* m_pRenderer = NULL;

	// Other

	bool m_bRunning;
	int m_currentFrame;

	GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;

#endif
