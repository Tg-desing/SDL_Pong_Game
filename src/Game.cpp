#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <chrono>
#include <thread>
#include "enum.h"
#include "Game.h"
#include "Text.h"
#include "GameProcess.h"
#include <SDL2/SDL2_TTF/SDL_ttf.h>
#include <filesystem>
#include "Vec2.h"

int WIDTH = 900;
int HEIGHT = 600;
int BALLWIDTH = 10;
int BALLHEIGHT = 10;
int WINSCORE = 5;
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
               pBall(NULL),
               currentFilePath(fs::current_path()),
               winscore(WINSCORE),
               winner(WINSIDE::NONE)
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

bool Game::init(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pTextFont, TTF_Font *&pScoreFont)
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
        printf("SDL setting TTF failed\n");
        return false;
    }

    fs::path textFontPath = currentFilePath / "text" / "emulogic-font" / "Emulogic-zrEw.ttf";
    pTextFont = TTF_OpenFont(textFontPath.string().c_str(), 56);

    if (pTextFont == nullptr)
    {
        printf("Font load failed\n");
        return false;
    }

    fs::path scoreFontPath = currentFilePath / "text" / "pong-score" / "pong-score.ttf";
    pScoreFont = TTF_OpenFont(scoreFontPath.string().c_str(), 28);
    if (pScoreFont == nullptr)
    {
        printf("Font load failed\n");
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
    if (gameWinSide == WINSIDE::LEFT)
    {
        score[(int)(WINSIDE::LEFT)]++;
    }
    else if (gameWinSide == WINSIDE::RIGHT)
    {
        score[static_cast<int>(WINSIDE::RIGHT)]++;
    }
}

bool Game::IsGameScored()
{
    if (pBall->GetPos().x < 0)
    {
        gameWinSide = WINSIDE::RIGHT;
        return true;
    }
    else if (pBall->GetPos().x > WIDTH - BALLWIDTH)
    {
        gameWinSide = WINSIDE::LEFT;
        return true;
    }
    return false;
}

void Game::RenderScoreText(SDL_Renderer *pRenderer, TTF_Font *pScoreFont)
{
    SDL_TextTexture *textRenderer = new SDL_TextTexture();
    textRenderer->RenderText(pRenderer, pScoreFont, std::to_string(score[static_cast<int>(WINSIDE::LEFT)]).c_str(), {255, 255, 255, 255}, 200, 5);
    textRenderer->RenderText(pRenderer, pScoreFont, std::to_string(score[static_cast<int>(WINSIDE::RIGHT)]).c_str(), {255, 255, 255, 255}, WIDTH - 200, 5);
}

bool Game::CheckWinner()
{
    if (score[static_cast<int>(WINSIDE::LEFT)] == WINSCORE)
    {
        winner = WINSIDE::LEFT;
        return true;
    }
    else if (score[static_cast<int>(WINSIDE::RIGHT)] == WINSCORE)
    {
        winner = WINSIDE::RIGHT;
        return true;
    }
    return false;
}

void Game::Render(SDL_Renderer *pRenderer, TTF_Font *pTextFont)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    SDL_TextTexture *textRenderer = new SDL_TextTexture();
    textRenderer->RenderText(pRenderer, pTextFont, "Pong Game", {255, 255, 255, 255}, WIDTH / 2 - 250, HEIGHT / 2 - 100);
    TTF_SetFontSize(pTextFont, 28);
    textRenderer->RenderText(pRenderer, pTextFont, "Press Space to start", {255, 255, 255, 255}, WIDTH / 2 - 300, HEIGHT / 2);

    SDL_RenderPresent(pRenderer);
}

void Game::RenderEnd(SDL_Renderer *pRenderer, TTF_Font *pTextFont)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);
    SDL_TextTexture *textRender = new SDL_TextTexture();
    if (winner == WINSIDE::LEFT)
        textRender->RenderText(pRenderer, pTextFont, "PLAYER 1 WIN!", {255, 255, 255, 255}, WIDTH / 2 - 150, HEIGHT / 2 - 100);
    else
        textRender->RenderText(pRenderer, pTextFont, "PLAYER 2 WIN!", {255, 255, 255, 255}, WIDTH / 2 - 150, HEIGHT / 2 - 100);
    TTF_SetFontSize(pTextFont, 28);
    textRender->RenderText(pRenderer, pTextFont, "Press Space to restart", {255, 255, 255, 255}, WIDTH / 2 - 300, HEIGHT / 2);

    SDL_RenderPresent(pRenderer);
}

void Game::GameBackgroundRender(SDL_Renderer *pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    int middleLineX = WIDTH / 2 - 5;
    for (int i = 0; i < HEIGHT; i += 15)
    {
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_Rect rect = {middleLineX, i, 10, 10};
        SDL_RenderDrawRect(pRenderer, &rect);
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_RenderFillRect(pRenderer, &rect);
    }
}

void Game::Run(SDL_Renderer *pRenderer, TTF_Font *pScoreFont, TTF_Font *pTextFont)
{
    lastticks = curticks;
    int isGameStart = false;
    int isGameEnd = false;
    while (!done)
    {
        if (isGameStart && !isGameEnd)
            GameBackgroundRender(pRenderer);
        else if (isGameEnd && !isGameStart)
            RenderEnd(pRenderer, pTextFont);

        while (SDL_PollEvent(&event))
        {
            if (!isGameStart || isGameEnd)
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
                        isGameEnd = false;
                        pBall = new Ball(Vec2((float)WIDTH / 2.0 - (float)BALLWIDTH / 2.0f, (float)HEIGHT / 2.0f - (float)BALLHEIGHT / 2.0f));
                        pBall->Init(WINSIDE::NONE);
                        continue;
                    }
                }
            }
            else
            {
                gameProcess->Run(event);
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
                pBall->Init(gameWinSide);
                AddScore();
                gameWinSide = WINSIDE::NONE;
            }

            gameProcess->Update(pRenderer, pPaddles);
            RenderScoreText(pRenderer, pScoreFont);
            if (CheckWinner())
            {
                isGameStart = false;
                isGameEnd = true;
                delete pBall;
                delete gameProcess;
                delete pPaddles[0];
                delete pPaddles[1];
                score[0] = 0;
                score[1] = 1;
            }
        }
        SDL_RenderPresent(pRenderer);
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