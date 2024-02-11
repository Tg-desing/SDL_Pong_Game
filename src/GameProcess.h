#ifndef GAMEPROCESSH
#define GAMEPROCESSH

#include <SDL2/SDL.h>
#include "Paddle.h"

class GameProcess
{
public:
    GameProcess();
    GameProcess(int level);
    ~GameProcess();

private:
    Paddle **pPaddles = new Paddle *[2];
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
    }

public:
    void Init(SDL_Renderer *pRenderer);
    void Run();
    void Update();

public:
    int level;
};

#endif