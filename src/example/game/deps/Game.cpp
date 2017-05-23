#include "Game.h"
#include "TextureManager.h"

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
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if(m_pRenderer != 0) {
				std::cout << "Successful: Init\n";

				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

				TheTextureManager::Instance()->load(
					"assets/sprites_002_magefalldown.png",
					"animate", m_pRenderer
				);

				m_gameObjects.push_back(new Player(new LoaderParams(0, 0, 65, 65,
					"animate")));

				m_gameObjects.push_back(new Enemy(new LoaderParams(0, 100, 65, 65,
					"animate")));

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

	for (vector<GameObject*>::size_type i = 0;
	i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}

	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 200) % 6));

	for (vector<GameObject*>::size_type i = 0;
	i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void Game::handleEvents()
{
	SDL_Event event;

	if(SDL_PollEvent(&event)) {

		bool KEYS[322];

		for(int i = 0; i < 322; i++) {
			KEYS[i] = false;
		}

		switch(event.type) {
			case SDL_QUIT:
				m_bRunning = false;
			break;

			case SDL_KEYDOWN:
				KEYS[event.key.keysym.sym] = true;
			break;

			case SDL_KEYUP:
				KEYS[event.key.keysym.sym] = false;
			break;

			default:
			break;
		}

		if(KEYS[SDLK_ESCAPE]) {
			clean();
			m_bRunning = false;
			printf("Key: ECS\n");
			printf("Quiting...\n");
		}
	}
}

bool Game::running()
{
	return m_bRunning;
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
