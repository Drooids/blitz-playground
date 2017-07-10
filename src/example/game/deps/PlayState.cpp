#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if(TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for(int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}

	if(
		checkCollision(
			dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
			dynamic_cast<SDLGameObject*>(m_gameObjects[1])
		)
	) {
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
	}
}

void PlayState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

void PlayState::handleEvents()
{

}

bool PlayState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_playID, &m_gameObjects, &m_textureIDList);

	printf("entering PlayState\n");
	return true;
}

bool PlayState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++) {
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	printf("Exit PlayState\n");
	return false;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if( bottomA <= topB ) {return false;}
	if( topA >= bottomB ) {return false; }
	if( rightA <= leftB ) {return false; }
	if( leftA >= rightB ) {return false;}

	return true;
}
