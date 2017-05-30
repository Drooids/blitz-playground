#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() :
	m_keystates(NULL),
	m_bJoysticksInitialised(false),
	m_mousePosition(new Vector2D(0, 0))
{
	for (int i = 0; i < 3; i++) {
		m_mouseButtonStates.push_back(false);
	}
}

InputHandler::~InputHandler()
{
	// delete anything we created dynamically
	delete m_mousePosition;

	// clear our arrays
	/*
	m_joystickValues.clear();
	m_joysticks.clear();
	m_buttonStates.clear();
	m_mouseButtonStates.clear();
	*/
}


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

bool InputHandler::joysticksInitialised() {
	return m_bJoysticksInitialised;
}

bool InputHandler::getButtonState(int joy, int buttonNumber) {
	return m_buttonStates[joy][buttonNumber];
}


bool InputHandler::getMouseButtonState(int buttonNumber) {
	return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition() {
	return m_mousePosition;
}

void InputHandler::update()
{
	SDL_Event event;

	if(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				TheGame::Instance()->quit();
				break;

			case SDL_JOYAXISMOTION:
				std::cout << "SDL_JOYAXISMOTION" << endl;
				onJoystickAxisMove(event);
				break;

			case SDL_JOYBUTTONDOWN:
				std::cout << "SDL_JOYBUTTONDOWN" << endl;
				onJoystickButtonDown(event);
				break;

			case SDL_JOYBUTTONUP:
				std::cout << "SDL_JOYBUTTONUP" << endl;
				onJoystickButtonUp(event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				std::cout << "SDL_MOUSEBUTTONDOWN" << endl;
				onMouseButtonDown(event);
				break;

			case SDL_MOUSEBUTTONUP:
				std::cout << "SDL_MOUSEBUTTONUP" << endl;
				onMouseButtonUp(event);
				break;

			case SDL_MOUSEMOTION:
				onMouseMove(event);
				break;

			case SDL_KEYDOWN:
				std::cout << "SDL_KEYDOWN: " << event.key.keysym.scancode << endl;
				onKeyDown();
				if (onKeyDown(SDL_SCANCODE_ESCAPE)) {
					TheGame::Instance()->quit();
					std::cout << "Key: ECS\n" << endl;
					std::cout << "Quiting...\n" << endl;
				}
				break;

			case SDL_KEYUP:
				std::cout << "SDL_KEYUP: " << event.key.keysym.scancode << endl;
				onKeyUp();
				break;
		}
	}
}

void InputHandler::onKeyDown()
{
	// Use this function to get a snapshot of the current state of the keyboard.
	m_keystates = SDL_GetKeyboardState(NULL);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(NULL);
}

bool InputHandler::onKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0) {
		if (m_keystates[key] == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	return false;
}

void InputHandler::onMouseMove(SDL_Event &event)
{
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onJoystickAxisMove(SDL_Event &event)
{
	int whichOne = event.jaxis.which;

	// left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
	}

	// left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
	}

	// right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setX(0);
		}
	}

	// right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setY(0);
		}
	}
}

void InputHandler::onJoystickButtonDown(SDL_Event &event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event &event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
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
