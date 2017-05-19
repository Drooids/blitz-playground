#ifndef GAMEOBJECECT_H_DEFINED
#define GAMEOBJECECT_H_DEFINED

#include <string>
#include <SDL.h>

#include "TextureManager.h"

using namespace std;

class GameObject
{
public:

	~GameObject();

	// The virtual keyword means that when calling this function through a pointer, it uses
	// the definition from the type of the object itself, not the type of its pointer
    virtual void load(int x, int y, int width, int height, string textureID);
    virtual void draw(SDL_Renderer* pRenderer);
    virtual void update();
    virtual void clean();

protected:

	// GameObject();

    string m_textureID;

    int m_currentFrame;
    int m_currentRow;

    int m_x;
    int m_y;

    int m_width;
    int m_height;
};

#endif
