#ifndef MENUBUTTON_H_DEFINED
#define MENUBUTTON_H_DEFINED

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "InputHandler.h"

/*
	Note:
	Public Inherintance
	All Public members of the Base Class become Public Members of the derived class &
	All Protected members of the Base Class become Protected Members of the Derived Class.
*/
class MenuButton : public SDLGameObject
{
public:
	MenuButton(const LoaderParams* pParams);

	virtual void draw();
	virtual	void update();
	virtual void clean();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
};

#endif
