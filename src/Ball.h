#ifndef BALL_H
#define BALL_H

#include "Vec2.h"
#include "Paddle.h"
#include <SDL2/SDL.h>

class Ball
{
private:
    Vec2 velocity;
    Vec2 pos;
    float bounceAngle;
    Vec2 DIRECTION;
    float movement;

public:
    Ball(Vec2 ballPos);
    ~Ball();

    void Init();
    void UpdatePos(Paddle **pPaddles);
    void Render(SDL_Renderer *pRenderer);

public:
    Vec2 GetPos()
    {
        return pos;
    }

private:
    int IsPaddleCollide(Paddle *paddle);
    int IsWallCollide();
};

#endif