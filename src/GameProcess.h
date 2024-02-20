#ifndef GAMEPROCESSH
#define GAMEPROCESSH

#include <SDL2/SDL.h>
#include "Paddle.h"
#include "Queue.h"
#include "Ball.h"
#include "Vec2.h"
#include <stdio.h>
// extern int const WIDTH, HEIGHT;
class GameProcess
{
public:
    GameProcess();
    GameProcess(int level);
    ~GameProcess();

private:
    bool isWKeyPressed = false;
    bool isSKeyPressed = false;
    bool isUpKeyPressed = false;
    bool isDownKeyPressed = false;
    Paddle **pPaddles = new Paddle *[2];
    Ball *pBall;
    // paddle object list
    // ball object

private:
    void setPaddles()
    {
        Paddle *paddle1 = new Paddle(1);
        paddle1->Init();
        Paddle *paddle2 = new Paddle(2);
        paddle2->Init();
        pPaddles[0] = paddle1;
        pPaddles[1] = paddle2;
    };

    void setBall()
    {
        int WIDTH = 900;
        int HEIGHT = 600;
        printf("WIDTH: %d, HEIGHT: %d\n", WIDTH, HEIGHT);
        Vec2 initialPos = Vec2((float)WIDTH / 2.0f - 10.0f, (float)HEIGHT / 2.0f - 10.0f);
        pBall = new Ball(initialPos);
        pBall->Init();
    };

public:
    void Init(SDL_Renderer *pRenderer);
    void Run(SDL_Event event);
    void Update(SDL_Renderer *pRenderer);
    void UpdatePos();

public:
    int level;
};

#endif