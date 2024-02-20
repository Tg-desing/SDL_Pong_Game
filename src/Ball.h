#ifndef BALL_H
#define BALL_H

#include "Vec2.h"
#include <SDL2/SDL.h>

class Ball
{
public:
    Vec2 velocity = Vec2(0, 0);
    static float DIRECTION[2];
    float movement;
    Vec2 pos;

public:
    Ball(Vec2 ballPos);
    ~Ball();

    void Init();
    void UpdatePos();
    void Render(SDL_Renderer *pRenderer);

private:
    int Collide(int paddleX, int paddle);
};

#endif