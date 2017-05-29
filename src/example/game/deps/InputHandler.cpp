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

				// Joysticks

				m_joysticks.push_back(joy);

				// First and the second sticks
				m_joystickValues.push_back(
					std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))
				);

				// Note: Probably a map would be better
				std::vector<bool> tempButton;

				// Get the number of joystick buttons
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
					tempButton.push_back(false);
				}
				m_buttonStates.push_back(tempButton);

				// Mouse

				for(int i = 0; i < 3; i++) {
					m_mouseButtonStates.push_back(false);
				}

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

		switch(event.type) {
			case SDL_QUIT:
				TheGame::Instance()->quit();
				break;

			case SDL_KEYDOWN:
				std::cout << "SDL_KEYDOWN: " << event.key.keysym.scancode << endl;
				m_activeKeys[event.key.keysym.scancode] = true;
				break;

			case SDL_KEYUP:
				std::cout << "SDL_KEYUP: " << event.key.keysym.scancode << endl;
				m_activeKeys[event.key.keysym.scancode] = false;
				break;

			case SDL_JOYAXISMOTION || // type value
				SDL_JOYBUTTONDOWN ||
				SDL_JOYBUTTONUP:

				std::cout << "SDL_JOYAXISMOTION || SDL_JOYBUTTONDOWN ..." << endl;

				if (SDL_JOYAXISMOTION) {

					int whichOne = event.jaxis.which; // get which controller

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
					int whichOne = event.jaxis.which; // get which controller
					std::cout << "SDL_JOYBUTTONDOWN" << endl;
					m_buttonStates[whichOne][event.jbutton.button] = true;
				}

				if (SDL_JOYBUTTONUP) {
					int whichOne = event.jaxis.which; // get which controller
					std::cout << "SDL_JOYBUTTONUP" << endl;
					m_buttonStates[whichOne][event.jbutton.button] = false;
				}

				break;

				case SDL_MOUSEBUTTONDOWN:

					std::cout << "SDL_MOUSEBUTTONDOWN: " << event.button.button
						<< "Clicks: " << event.button.clicks
						<< endl;

					if(event.button.button == SDL_BUTTON_LEFT) {
						m_mouseButtonStates[LEFT] = true;
					}

					if(event.button.button == SDL_BUTTON_MIDDLE) {
						m_mouseButtonStates[MIDDLE] = true;
					}

					if(event.button.button == SDL_BUTTON_RIGHT) {
						m_mouseButtonStates[RIGHT] = true;
					}

					break;

				case SDL_MOUSEBUTTONUP:

					if(event.button.button == SDL_BUTTON_LEFT) {
						m_mouseButtonStates[LEFT] = true;
					}

					if(event.button.button == SDL_BUTTON_MIDDLE) {
						m_mouseButtonStates[MIDDLE] = true;
					}

					if(event.button.button == SDL_BUTTON_RIGHT) {
						m_mouseButtonStates[RIGHT] = true;
					}

					break;

		}

		if(m_activeKeys[SDL_SCANCODE_ESCAPE]) {
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
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}


