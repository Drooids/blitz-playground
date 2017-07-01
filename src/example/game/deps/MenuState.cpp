#include "MenuState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	handleEvents();

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

void MenuState::handleEvents()
{
	if (TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->quit();
	}
}

bool MenuState::onEnter()
{
	std::string pb = "playbutton";
	std::string eb = "exitbutton";

	if (!TheTextureManager::Instance()->load(
		"assets/button.png",
		pb,
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load(
		"assets/exit.png",
		eb,
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 =
		new MenuButton(new LoaderParams(100, 100, 400, 100, pb), s_menuToPlay);
	GameObject* button2 =
		new MenuButton(new LoaderParams(100, 300, 400, 100, eb), s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

	std::cout << "Exiting MenuState\n";
	return false;
}

void MenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}
