#ifndef BASECREATOR_H_DEFINED
#define BASECREATOR_H_DEFINED

#include <string>
#include <map>
#include "GameObject.h"

// This class's only purpose is the creation of a specific object.

class BaseCreator
{

public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {};
};

#endif
