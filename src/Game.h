#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_TTF/SDL_ttf.h>
#include "GameProcess.h"
#include "Ball.h"
#include "Paddle.h"

class Game
{
private:
    static Game *instance;
    Game();
    ~Game();

public:
    static Game *GetInstance();
    bool init(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pFont);
    void Render(SDL_Renderer *pRenderer, TTF_Font *pFont);
    void Run(SDL_Renderer *pRenderer, TTF_Font *pFont);

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

    int IsGameScored();

    void RenderScoreText(SDL_Renderer *pRenderer, TTF_Font *pFont);

private:
    GameProcess *gameProcess;
    Ball *pBall;
    Paddle **pPaddles = new Paddle *[2];
    int score[2] = {0, 0};
    int gameWinFlag = 0;
};

#endif