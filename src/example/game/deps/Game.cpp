#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width,
    int height, int flags)
{

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";

        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(m_pWindow != 0) {
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if(m_pRenderer != 0)
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
            else
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
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{

}

void Game::handleEvents()
{
    SDL_Event event;

    if(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                m_bRunning = false;
            break;

            default:
            break;
        }
    }
}

bool Game::running() {
    return m_bRunning;
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
