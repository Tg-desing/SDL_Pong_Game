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

public:
    void Init(SDL_Renderer *pRenderer);
    void Run(SDL_Event event);
    void Update(SDL_Renderer *pRenderer, Paddle **pPaddles);
    void UpdatePos(Paddle **pPaddles);

public:
    int level;
};

#endif