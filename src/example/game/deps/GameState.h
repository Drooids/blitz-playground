#ifndef GAMESTATE_H_DEFINED
#define GAMESTATE_H_DEFINED

#include <string>
#include <iostream>
#include <vector>

class GameState
{
public:

	// GameState();
	// ~GameState();

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

protected:
	std::vector<std::string> m_textureIDList;
};

#endif
