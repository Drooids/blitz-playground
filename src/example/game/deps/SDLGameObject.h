#ifndef SDLGAMEOBJECT_H_DEFINED
#define SDLGAMEOBJECT_H_DEFINED

#include "LoaderParams.h"
#include "GameObject.h"
#include "Vector2D.h"

#include <string>

class SDLGameObject : public GameObject
{
public:

	SDLGameObject(const LoaderParams* pParams, int numFrames = 1,
		int frameChangeSpeed = 1);

	virtual void draw();
	virtual void update();
	virtual void clean();

	Vector2D& getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

protected:

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	int m_frameChangeSpeed;

	string m_textureID;
};

#endif
