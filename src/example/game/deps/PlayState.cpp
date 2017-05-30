#include "PlayState.h"

const std::string PlayState::s_menuID = "PLAYE";

void PlayState::update()
{
	// nothing for now
}

void PlayState::render()
{
	// Nothing for now
}

bool PlayState::onEnter()
{
	std::cout << "Entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting PlayState\n";
	return false;
}
