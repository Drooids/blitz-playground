#ifndef INPUTHANDLER_H_DEFINED
#define INPUTHANDLER_H_DEFINED

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_main.h>

#include "Vector2D.h"

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

	// Joystick

	void initializeJoysticks();

	// of the joystick we want to use, and  the stick is
	// 1 for the left stick and 2 for the right stick
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	bool joysticksInitialised() {
		return m_bJoysticksInitialised;
	}

	bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	// Keyboard

private:
	// InputHandler();
	~InputHandler();

	static InputHandler* s_pInstance;

	// Joystick

	std::vector<SDL_Joystick*> m_joysticks;

	/*
		The Xbox 360 controller uses axes 2 and 5 for the analog triggers. To handle multiple
		controllers with multiple axes we will create a vector of pairs of Vector2D*, one for
		each stick.
		std::pair<Vector2D*, Vector2D*> vectors per each stick, which keeps track of their positions.
		std::pair <std::string,double> aPair ("A", 1);
		aPair.first == "A"; aPair.second == 1;
		More one std::pair http://www.cplusplus.com/reference/utility/pair/pair/
	*/
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

	/*
		The region(or amount of movement) that the joystick can
		physically move without registering any change is the deadzone for the stick.
		Varies from model to model, in some you can even adjust manually
		or by software the amount of deadzone in both the X and Y axis.

		The way SDL handles analog sticks on a game controller is that it converts
		its position into a number between -32768 to 32767

		Sensitivity of a controller.

		Change this value for different type of controllers, such as: ps2|3|4; xbox...
	*/
	const int m_joystickDeadZone = 10000;

	std::vector<std::vector<bool>> m_buttonStates;

	// Keyboard

	// Currently active keys
	std::map<int, bool> m_activeKeys;


	// Mouse

	// Currently active buttons
	std::vector<bool> m_mouseButtonStates;

	bool m_bJoysticksInitialised;
};

typedef InputHandler TheInputHandler;

#endif
