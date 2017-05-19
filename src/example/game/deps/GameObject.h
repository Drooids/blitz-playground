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

    void load(int x, int y, int width, int height, string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean();

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
