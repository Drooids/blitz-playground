#ifndef MENUBUTTON_H_DEFINED
#define MENUBUTTON_H_DEFINED

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "InputHandler.h"
#include "BaseCreator.h"

/*
	Note:
	Public Inherintance
	All Public members of the Base Class become Public Members of the derived class &
	All Protected members of the Base Class become Protected Members of the Derived Class.
*/
class MenuButton : public SDLGameObject
{
public:
	MenuButton();
	// virtual ~MenuButton() {}

	virtual void load(const LoaderParams *pParams);
	virtual void draw();
	virtual	void update();
	virtual void clean();

	void setCallback(void(*callback)()) { m_callback = callback; }
	int getCallbackID() { return m_callbackID; };

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void (*m_callback)();

	int m_callbackID;
	bool m_bReleased;
};

class MenuButtonCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new MenuButton();
    }
};

#endif
