#include "MenuState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	// nothing for now
}

void MenuState::render()
{
	// Nothing for now
}

bool MenuState::onEnter()
{
	std::cout << "Entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	std::cout << "Exiting MenuState\n";
	return false;
}
