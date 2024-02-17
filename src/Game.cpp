#include <stdio.h>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include "Game.h"
#include "Text.h"
#include "GameProcess.h"
#include <SDL2/SDL2_TTF/SDL_ttf.h>

static const int WIDTH = 800;
static const int HEIGHT = 600;

Game *Game::instance = NULL;

int Game::curticks = 0;
int Game::lastticks = 0;
float Game::fps = 0;
int Game::framecount = 0;
int Game::done = 0;
SDL_Event Game::event;
Game::Game()
{
}

Game::~Game()
{
}

Game *Game::GetInstance()
{
    if (instance == NULL)
    {
        instance = new Game();
    }
    return instance;
}

bool Game::init(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pFont)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    pWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (pWindow == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

    if (pRenderer == NULL)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL setting TTF failed");
        return false;
    }

    pFont = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 28);
    if (pFont == nullptr)
    {
        printf("Font load failed");
        return false;
    }

    lastticks = SDL_GetTicks();
    curticks = lastticks;
    fps = 0;
    framecount = 0;
    done = false;

    return true;
}

void Game::Render(SDL_Renderer *pRenderer, TTF_Font *pFont)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    SDL_TextTexture *textRenderer = new SDL_TextTexture();
    textRenderer->RenderText(pRenderer, pFont, "Pong Game", {255, 255, 255, 255}, 50, 50);

    SDL_RenderPresent(pRenderer);
}

void Game::Run(SDL_Renderer *pRenderer)
{
    lastticks = curticks;
    int isGameStart = false;
    while (!done)
    {
        while (SDL_PollEvent(&event))
        {
            if (!isGameStart)
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        gameProcess = new GameProcess(1);
                        gameProcess->Init(pRenderer);
                        isGameStart = true;
                        break;
                    }
                }
            }
            else
            {
                gameProcess->Run(event);
                gameProcess->UpdatePos();
                gameProcess->Update(pRenderer);
                // GameProcess->Run();
            }
        }
        // GameProcess->Update();
        SDL_RenderPresent(pRenderer);
        curticks = SDL_GetTicks();
        fps = 1000.0 / 60.0;
        int sleepTime = fps - (curticks - lastticks);
        // sleep process
        lastticks = curticks;
        framecount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
}