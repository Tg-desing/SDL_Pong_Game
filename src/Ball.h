#ifndef BALL_H
#define BALL_H

#include "Vec2.h"
#include "Paddle.h"
#include <SDL2/SDL.h>

class Ball
{
public:
    Vec2 velocity = Vec2(0, 0);
    Vec2 DIRECTION = Vec2(1.0f, -1.0f);
    float movement;
    Vec2 pos;

public:
    Ball(Vec2 ballPos);
    ~Ball();

    void Init();
    void UpdatePos(Paddle **pPaddles);
    void Render(SDL_Renderer *pRenderer);

private:
    int IsPaddleCollide(Paddle *paddle);
    int IsWallCollide();
};

#endif