#include "Game.h"

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

                SDL_Surface* pTempSurface = IMG_Load("assets/sprites_001.png");

                if(pTempSurface == NULL) {
                    printf("SDL_Init failed: %s\n", SDL_GetError());
                    return false;
                }

                m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

                SDL_FreeSurface(pTempSurface);

                SDL_QueryTexture(m_pTexture, NULL, NULL,
                    &m_sourceRectangle.w, &m_sourceRectangle.h);

                m_destinationRectangle.x = m_sourceRectangle.x = 105;
                m_destinationRectangle.y = m_sourceRectangle.y = 50;

                m_sourceRectangle.w = 35;
                m_sourceRectangle.h = 40;

                m_destinationRectangle.w = m_sourceRectangle.w;
                m_destinationRectangle.h = m_sourceRectangle.h;

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
    SDL_RenderCopy(m_pRenderer, m_pTexture,
        &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    m_sourceRectangle.x = 105 + (40 * int(((SDL_GetTicks() / 200) % 5)));
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

bool Game::running() {
    return m_bRunning;
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
