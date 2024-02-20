#include <SDL2/SDL.h>
#include "GameProcess.h"
#include "Paddle.h"
#include "Ball.h"

GameProcess::GameProcess() {}
GameProcess::~GameProcess() {}
GameProcess::GameProcess(int level) : level(level) {}

void GameProcess::Init(SDL_Renderer *pRenderer)
{
    setPaddles();
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);
}

void GameProcess::Run(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            isWKeyPressed = true;
            break;
        case SDLK_s:
            isSKeyPressed = true;
            break;
        case SDLK_UP:
            isUpKeyPressed = true;
            break;
        case SDLK_DOWN:
            isDownKeyPressed = true;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            isWKeyPressed = false;
            break;
        case SDLK_s:
            isSKeyPressed = false;
            break;
        case SDLK_UP:
            isUpKeyPressed = false;
            break;
        case SDLK_DOWN:
            isDownKeyPressed = false;
            break;
        }
        break;
    default:
        break;
    }
}

void GameProcess::UpdatePos()
{
    if (isWKeyPressed)
    {
        pPaddles[0]->UpdatePosY(-1);
    }
    if (isSKeyPressed)
    {
        pPaddles[0]->UpdatePosY(1);
    }
    if (isUpKeyPressed)
    {
        pPaddles[1]->UpdatePosY(-1);
    }
    if (isDownKeyPressed)
    {
        pPaddles[1]->UpdatePosY(1);
    }
}
void GameProcess::Update(SDL_Renderer *pRenderer)
{
    pPaddles[0]->Render(pRenderer);
    pPaddles[1]->Render(pRenderer);
}