#include "BaseCreator.h"
#include "Player.h"

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new Player();
	}
};
