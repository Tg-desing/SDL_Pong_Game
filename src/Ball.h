#ifndef BALL_H
#define BALL_H
#include "enum.h"
#include "Vec2.h"
#include "Paddle.h"
#include "Game.h"
#include <SDL2/SDL.h>

class Ball
{

private:
    float velocity;
    Vec2 pos;
    float bounceAngle;
    Vec2 DIRECTION;
    float movement;
    wallCollideType collideType;
    bool firstCollide;

public:
    Ball(Vec2 ballPos);
    ~Ball();

    void Init(WINSIDE winSide);
    void UpdatePos(Paddle **pPaddles);
    void Render(SDL_Renderer *pRenderer);

public:
    Vec2 GetPos()
    {
        return pos;
    }

private:
    int IsPaddleCollide(Paddle *paddle);
    bool IsWallCollide();
};

#endif