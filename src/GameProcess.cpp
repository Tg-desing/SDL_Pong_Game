#include <SDL2/SDL.h>
#include "GameProcess.h"
#include "Paddle.h"

GameProcess::GameProcess() {}
GameProcess::~GameProcess() {}
GameProcess::GameProcess(int level) : level(level) {}

void GameProcess::Init(SDL_Renderer *pRenderer)
{
    setPaddles();
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    pPaddles[0]->Render(pRenderer);
    pPaddles[1]->Render(pRenderer);
}

void GameProcess::Run() {}
void GameProcess::Update() {}