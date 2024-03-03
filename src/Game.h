#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_TTF/SDL_ttf.h>
#include <filesystem>
#include "enum.h"
#include "GameProcess.h"
#include "Ball.h"
#include "Paddle.h"

namespace fs = std::filesystem;

class Ball;

class Game
{
private:
    static Game *instance;
    Game();
    ~Game();

public:
    static Game *GetInstance();
    bool init(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pTextFont, TTF_Font *&pScoreFont);
    void Render(SDL_Renderer *pRenderer, TTF_Font *pTextFont);
    void Run(SDL_Renderer *pRenderer, TTF_Font *pScoreFont);
    void GameBackgroundRender(SDL_Renderer *pRenderer);
    void RenderEnd(SDL_Renderer *pRenderer, TTF_Font *pTextFont);

public:
    static int lastticks;
    static int curticks;
    static float fps;
    static int framecount;
    static SDL_Event event;
    static int done;
    static int durationTime;

public:
    void setPaddles()
    {
        Paddle *paddle1 = new Paddle(1);
        paddle1->Init();
        Paddle *paddle2 = new Paddle(2);
        paddle2->Init();
        pPaddles[0] = paddle1;
        pPaddles[1] = paddle2;
    };

    void AddScore();

    bool IsGameScored();

    void RenderScoreText(SDL_Renderer *pRenderer, TTF_Font *pScoreFont);

private:
    GameProcess *gameProcess;
    Ball *pBall;
    Paddle **pPaddles = new Paddle *[2];
    int score[2] = {0, 0};
    WINSIDE gameWinSide = WINSIDE::NONE;
    fs::path currentFilePath;
};

#endif