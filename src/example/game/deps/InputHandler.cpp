#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::initializeJoysticks()
{
	/*
		First we check whether the joystick
		subsystem has been initialized using SDL_WasInit. If it has not been
		initialized we then initialize it using SDL_InitSubSystem
	*/
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0) {

		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (SDL_JoystickGetAttached(joy) == SDL_TRUE) {
				m_joysticks.push_back(joy);
			} else {
				std::cout << SDL_GetError();
			}
		}

		// Finally, we tell SDL to start listening for joystick events by enabling...
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;

		std::cout << "Initialized " << m_joysticks.size() << " joysticks(s)";

	} else {
		m_bJoysticksInitialised = false;
	}
}

void InputHandler::update()
{
	SDL_Event event;

	if(SDL_PollEvent(&event)) {

		bool KEYS[322];

		for(int i = 0; i < 322; i++) {
			KEYS[i] = false;
		}

		switch(event.type) {
			case SDL_QUIT:
				TheGame::Instance()->quit();
			break;

			case SDL_KEYDOWN:
				KEYS[event.key.keysym.sym] = true;
			break;

			case SDL_KEYUP:
				KEYS[event.key.keysym.sym] = false;
			break;

			default:
			break;
		}

		if(KEYS[SDLK_ESCAPE]) {
			TheGame::Instance()->quit();
			printf("Key: ECS\n");
			printf("Quiting...\n");
		}
	}
}

void InputHandler::clean()
{
	if (m_bJoysticksInitialised) {
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

