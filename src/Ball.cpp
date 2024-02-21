#include "Ball.h"
#include <stdio.h>
#include "Vec2.h"
#include "Paddle.h"

extern int BALLWIDTH;
extern int BALLHEIGHT;
extern int HEIGHT;
Ball::Ball(Vec2 ballPos) : pos(ballPos) {}

void Ball::Init()
{
    velocity.x = 5.0f;
    velocity.y = 1.5f;
}

void Ball::UpdatePos(Paddle **pPaddles)
{
    if (IsWallCollide() == 1)
    {
        DIRECTION.y *= -1.0f;
    }

    if (IsPaddleCollide(pPaddles[0]) == 1)
    {
        DIRECTION.x *= -1.0f;
    }

    if (IsPaddleCollide(pPaddles[1]) == 1)
    {
        DIRECTION.x *= -1.0f;
    }
    pos += velocity * DIRECTION;
}

int Ball::IsWallCollide()
{
    static int flag = 1;
    if ((pos.y <= 0 || pos.y >= HEIGHT - BALLHEIGHT) && flag)
    {
        flag = 0;
        return 1;
    }
    flag = 1;
    return 0;
}

int Ball::IsPaddleCollide(Paddle *paddle)
{
    Vec2 paddlePos = paddle->GetPos();
    Vec2 paddleSize = paddle->GetSize();

    if (paddle->GetPlayerNum() == 1)
    {
        float collidePosX = paddlePos.x + paddleSize.x;
        float minCollidePosY = paddlePos.y;
        float maxCollidePosY = paddlePos.y + paddleSize.y;

        if (pos.x <= collidePosX && pos.y >= minCollidePosY && pos.y <= maxCollidePosY)
            return 1;
    }
    else
    {
        float collidePosX = paddlePos.x;

        float minCollidePosY = paddlePos.y;
        float maxCollidePosY = paddlePos.y + paddleSize.y;

        if ((pos.x + BALLWIDTH) >= collidePosX && pos.y >= minCollidePosY && pos.y <= maxCollidePosY)
            return 1;
    }

    return 0;
}
void Ball::Render(SDL_Renderer *pRenderer)
{
    SDL_Rect ball = {(int)pos.x, (int)pos.y, BALLWIDTH, BALLHEIGHT};
    SDL_RenderDrawRect(pRenderer, &ball);
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pRenderer, &ball);
}
