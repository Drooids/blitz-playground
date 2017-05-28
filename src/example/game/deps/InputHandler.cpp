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

			case SDL_JOYAXISMOTION || // type value
				SDL_JOYBUTTONDOWN ||
				SDL_JOYBUTTONUP:

				int whichOne = event.jaxis.which; // get which controller

				if (SDL_JOYAXISMOTION) {
					// Left stick

					// Move left or right
					// If the X axis changed
					if (event.jaxis.axis == 0) {
						if (event.jaxis.value > m_joystickDeadZone) {
							m_joystickValues[whichOne].first->setX(1);
						}
						else if (event.jaxis.value < -m_joystickDeadZone) {
							m_joystickValues[whichOne].first->setX(-1);
						}
						else {
							m_joystickValues[whichOne].first->setX(0);
						}
					}

					// Move up or down
					// If the Y axis changed
					if (event.jaxis.axis == 1) {
						if (event.jaxis.value > m_joystickDeadZone) {
							m_joystickValues[whichOne].first->setY(1);
						}
						else if (event.jaxis.value < -m_joystickDeadZone) {
							m_joystickValues[whichOne].first->setY(-1);
						}
						else {
							m_joystickValues[whichOne].first->setY(0);
						}
					}

					// Right stick

					// Move left or right
					if (event.jaxis.axis == 3) {
						if (event.jaxis.value > m_joystickDeadZone) {
							m_joystickValues[whichOne].second->setY(1);
						}
						else if (event.jaxis.value < -m_joystickDeadZone) {
							m_joystickValues[whichOne].second->setY(-1);
						}
						else {
							m_joystickValues[whichOne].second->setY(0);
						}
					}

					// Move up or down
					if (event.jaxis.axis == 4) {
						if (event.jaxis.value > m_joystickDeadZone) {
							m_joystickValues[whichOne].second->setY(1);
						}
						else if (event.jaxis.value < -m_joystickDeadZone) {
							m_joystickValues[whichOne].second->setY(-1);
						}
						else {
							m_joystickValues[whichOne].second->setY(0);
						}
					}

				}

				if (SDL_JOYBUTTONDOWN) {

				}

				if (SDL_JOYBUTTONUP) {

				}

				break;
		}

		if(KEYS[SDLK_ESCAPE]) {
			TheGame::Instance()->quit();
			std::cout << "Key: ECS\n" << endl;
			std::cout << "Quiting...\n" << endl;
		}
	}
}

int InputHandler::xvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0) {
		if (stick == 1) {
			return m_joystickValues[joy].first->getX();
		}
		else if (stick == 2) {
			return m_joystickValues[joy].second->getX();
		}
	}

	return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0) {
		if (stick == 1) {
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2) {
			return m_joystickValues[joy].second->getY();
		}
	}

	return 0;
}

void InputHandler::clean()
{
	if (m_bJoysticksInitialised) {
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}


