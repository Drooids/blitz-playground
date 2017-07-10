#include "GameOverState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::update()
{
	for(int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

void GameOverState::handleEvents()
{

}

bool GameOverState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	setCallbacks(m_callbacks);

	printf("Entering GameOverState\n");
	return true;
}

bool GameOverState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("helicopter");

	printf("Exit GameOverState\n");
	return false;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
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
