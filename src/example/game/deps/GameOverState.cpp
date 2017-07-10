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
	if(!TheTextureManager::Instance()->load("assets/gameover.png",
	"gameovertext", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if(!TheTextureManager::Instance()->load("assets/main.png",
	"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if(!TheTextureManager::Instance()->load("assets/restart.png",
	"restartbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	/*
	GameObject* ot = new AnimatedGraphic(
 		new LoaderParams(200, 100, 190, 30, "gameovertext"));

	GameObject* mb = new MenuButton(
		new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);

	GameObject* rb = new MenuButton(
		new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);

	m_gameObjects.push_back(ot);
	m_gameObjects.push_back(mb);
	m_gameObjects.push_back(rb);
	*/

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
