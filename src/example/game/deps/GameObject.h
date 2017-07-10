#ifndef GAMEOBJECECT_H_DEFINED
#define GAMEOBJECECT_H_DEFINED

#include "LoaderParams.h"

class GameObject
{
public:

	// The virtual keyword means that when calling this function through a pointer, it uses
	// the definition from the type of the object itself, not the type of its pointer
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	virtual void load(const LoaderParams* pParams) = 0;

protected:

	GameObject() {}
	virtual ~GameObject() {}
};

#endif
