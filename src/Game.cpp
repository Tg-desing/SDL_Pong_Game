#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <chrono>
#include <thread>
#include "Game.h"
#include "Text.h"
#include "GameProcess.h"
#include <SDL2/SDL2_TTF/SDL_ttf.h>
#include "Vec2.h"

int WIDTH = 900;
int HEIGHT = 600;
int BALLWIDTH = 10;
int BALLHEIGHT = 10;
Game *Game::instance = NULL;

#include "Ball.h"
int Game::curticks = 0;
int Game::lastticks = 0;
float Game::fps = 0;
int Game::framecount = 0;
int Game::done = 0;
int Game::durationTime = 0;
SDL_Event Game::event;
Game::Game() : gameProcess(NULL),
               pBall(NULL)
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

void Game::AddScore()
{
    if (gameWinFlag == 1)
    {
        score[0]++;
    }
    else if (gameWinFlag == 2)
    {
        score[1]++;
    }
}

int Game::IsGameScored()
{
    if (pBall->GetPos().x < 0)
    {
        gameWinFlag = 2;
        return 1;
    }
    else if (pBall->GetPos().x > WIDTH - BALLWIDTH)
    {
        gameWinFlag = 1;
        return 1;
    }
    return 0;
}

void Game::RenderScoreText(SDL_Renderer *pRenderer, TTF_Font *pFont)
{
    SDL_TextTexture *textRenderer = new SDL_TextTexture();
    textRenderer->RenderText(pRenderer, pFont, std::to_string(score[0]).c_str(), {255, 255, 255, 255}, 100, 5);
    textRenderer->RenderText(pRenderer, pFont, std::to_string(score[1]).c_str(), {255, 255, 255, 255}, WIDTH - 100, 5);
}

void Game::Render(SDL_Renderer *pRenderer, TTF_Font *pFont)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    SDL_TextTexture *textRenderer = new SDL_TextTexture();
    textRenderer->RenderText(pRenderer, pFont, "Pong Game", {255, 255, 255, 255}, 50, 50);

    SDL_RenderPresent(pRenderer);
}

void Game::Run(SDL_Renderer *pRenderer, TTF_Font *pFont)
{
    lastticks = curticks;
    int isGameStart = false;
    while (!done)
    {
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(pRenderer, WIDTH / 2, 0, WIDTH / 2, HEIGHT);

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
                        setPaddles();
                        gameProcess->Init(pRenderer);
                        isGameStart = true;
                        pBall = new Ball(Vec2((float)WIDTH / 2.0 - (float)BALLWIDTH / 2.0f, (float)HEIGHT / 2.0f - (float)BALLHEIGHT / 2.0f));
                        pBall->Init();
                        break;
                    }
                }
            }
            else
            {
                gameProcess->Run(event);

                // GameProcess->Run();
            }
        }

        if (isGameStart)
        {
            gameProcess->UpdatePos(pPaddles, durationTime);
            pBall->UpdatePos(pPaddles);
            pBall->Render(pRenderer);

            if (IsGameScored())
            {
                delete pBall;
                pBall = new Ball(Vec2((float)WIDTH / 2.0f - (float)BALLWIDTH / 2.0f, (float)HEIGHT / 2.0f - (float)BALLHEIGHT / 2.0f));
                pBall->Init();
                AddScore();
                gameWinFlag = 0;
            }

            gameProcess->Update(pRenderer, pPaddles);
            RenderScoreText(pRenderer, pFont);
            SDL_RenderPresent(pRenderer);
        }
        // GameProcess->Update();
        curticks = SDL_GetTicks();
        durationTime = curticks - lastticks;
        fps = 1000.0 / 30.0;
        int sleepTime = fps - durationTime;
        // sleep process
        lastticks = curticks;
        framecount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
}