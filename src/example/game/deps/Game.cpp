#include "Game.h"

Game* Game::s_pInstance = 0;

Game* Game::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new Game();
		return s_pInstance;
	}

	return s_pInstance;
};

bool Game::init(const char* title, int xpos, int ypos, int width,
	int height, int flags)
{

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		// Window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// Joystick Input handler
		TheInputHandler::Instance()->initializeJoysticks();

		if(m_pWindow != 0) {

			// Renderer
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if(m_pRenderer != 0) {
				std::cout << "Successful: Init\n";

				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

				m_pGameStateMachine = new GameStateMachine();
				m_pGameStateMachine->changeState(new MenuState());

				TheTextureManager::Instance()->load(
					"assets/sprites_002_magefalldown.png",
					"animate", m_pRenderer
				);

			} else
				return false;

		} else
			return false;

	} else
		return false;

	m_bRunning = true;

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	for (vector<GameObject*>::size_type i = 0;
	i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}

	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
 	m_pGameStateMachine->update();

	m_currentFrame = int(((SDL_GetTicks() / 200) % 6));
	for (vector<GameObject*>::size_type i = 0;
	i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();

	if (TheInputHandler::Instance()->onKeyDown(SDL_SCANCODE_RETURN)) {
		m_pGameStateMachine->changeState(new PlayState());
	}
}

bool Game::running()
{
	return m_bRunning;
}

void Game::clean()
{
	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
