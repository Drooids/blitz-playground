#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "GameObject.h"

using namespace std;

class Player : public GameObject
{
public:

	~Player();

    void load(int x, int y, int width, int height, string textureID);
    void draw(SDL_Renderer* pRenderer);
    void update();
    void clean();

protected:
	// ...
};

#endif
