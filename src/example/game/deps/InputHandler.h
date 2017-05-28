#ifndef INPUTHANDLER_H_DEFINED
#define INPUTHANDLER_H_DEFINED

#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_main.h>

/*
	https://wiki.libsdl.org/SDL_JoyAxisEvent

	SDL joystick event 	Purpose
	---------------------------------------------------------
	SDL_JoyAxisEvent 	Axis motion information
	SDL_JoyButtonEvent 	Button press and release information
	SDL_JoyBallEvent 	Trackball event motion information
	SDL_JoyHatEvent 	Joystick hat position change

	SDL joystick event 	Type value
	---------------------------------------------------------
	SDL_JoyAxisEvent 	SDL_JOYAXISMOTION
	SDL_JoyButtonEvent 	SDL_JOYBUTTONDOWN or
						SDL_JOYBUTTONUP
	SDL_JoyBallEvent 	SDL_JOYBALLMOTION
	SDL_JoyHatEvent 	SDL_JOYHATMOTION
*/
class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	void update();
	void clean();

	void initializeJoysticks();
	bool joysticksInitialised() {
		return m_bJoysticksInitialised;
	}

private:
	// InputHandler();
	~InputHandler();

	static InputHandler* s_pInstance;

	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialised;
};

typedef InputHandler TheInputHandler;

#endif
