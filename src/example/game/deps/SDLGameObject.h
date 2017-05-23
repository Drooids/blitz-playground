#ifndef SDLGAMEOBJECT_H_DEFINED
#define SDLGAMEOBJECT_H_DEFINED

#include "LoaderParams.h"
#include "GameObject.h"

#include <string>

using namespace std;

class SDLGameObject : public GameObject
{
public:

	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	string m_textureID;
};

#endif
