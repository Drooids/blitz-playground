#include "MainMenuState.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	handleEvents();

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

void MainMenuState::handleEvents()
{
	if (TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->quit();
	}
}

bool MainMenuState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0); // Start from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	setCallbacks(m_callbacks);

	std::cout << "Entering MainMenuState\n";
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for(int i = 0; i < m_gameObjects.size(); i++) {

		// We use dynamic_cast to check whether the object is a MenuButton type;
		// if it is then we do the actual cast and then use the objects
		// callbackID as the index
		// into the callbacks vector and assign the correct function
		if(dynamic_cast<MenuButton*>(m_gameObjects[i])) {
			MenuButton* pButton =
				dynamic_cast<MenuButton*>(m_gameObjects[i]);

				pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

bool MainMenuState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

 	/* clear the texture manager
    for(unsigned int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }
	*/

    TheInputHandler::Instance()->reset();

	printf("Exiting MainMenuState\n");
	return false;
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}
