#include "Ball.h"
#include <cmath>
#include <stdio.h>
#include "Vec2.h"
#include "Paddle.h"
using namespace std;

extern int BALLWIDTH;
extern int BALLHEIGHT;
extern int HEIGHT;
Ball::Ball(Vec2 ballPos) : velocity(Vec2(10.0f, 10.0f)), pos(ballPos), bounceAngle(0.0f), DIRECTION(Vec2(1.0f, 0.0f)) {}
Ball::~Ball() {}

void Ball::Init()
{
}

void Ball::UpdatePos(Paddle **pPaddles)
{
    if (IsWallCollide() == 1)
    {
        DIRECTION.y *= -1.0f;
    }

    if (IsPaddleCollide(pPaddles[0]) == 1)
    {
        DIRECTION.y = -sin(bounceAngle * 3.14f / 180.0f);
        DIRECTION.x = cos(bounceAngle * 3.14f / 180.0f);
    }

    if (IsPaddleCollide(pPaddles[1]) == 1)
    {
        DIRECTION.y = -sin(bounceAngle * 3.14f / 180.0f);
        DIRECTION.x = -cos(bounceAngle * 3.14f / 180.0f);
    }
    pos += velocity * DIRECTION;
}

int Ball::IsWallCollide()
{
    if ((pos.y <= 0 || pos.y >= HEIGHT - BALLHEIGHT))
    {
        return 1;
    }
    return 0;
}

int Ball::IsPaddleCollide(Paddle *paddle)
{
    Vec2 paddlePos = paddle->GetPos();
    Vec2 paddleSize = paddle->GetSize();

    if (paddle->GetPlayerNum() == 1)
    {
        float minCollidePosY = paddlePos.y;
        float maxCollidePosY = paddlePos.y + paddleSize.y - (float)BALLWIDTH;

        if (pos.y <= maxCollidePosY && pos.y >= minCollidePosY)
        {
            if (pos.x <= (paddlePos.x + paddleSize.x) && pos.x > paddlePos.x)
            {
                float relativeIntersectY = (paddlePos.y + paddleSize.y / 2) - pos.y;
                float normalizedRelativeIntersectY = relativeIntersectY / (paddleSize.y / 2);
                bounceAngle = normalizedRelativeIntersectY * 80.0f;
                return 1;
            }
        }
    }
    else
    {

        float minCollidePosY = paddlePos.y;
        float maxCollidePosY = paddlePos.y + paddleSize.y - (float)BALLWIDTH;

        if (pos.y <= maxCollidePosY && pos.y >= minCollidePosY)
        {
            if (pos.x >= paddlePos.x && pos.x < (paddlePos.x + paddleSize.x))
            {
                float relativeIntersectY = (paddlePos.y + paddleSize.y / 2) - pos.y;
                float normalizedRelativeIntersectY = relativeIntersectY / (paddleSize.y / 2);
                bounceAngle = normalizedRelativeIntersectY * 80.0f;
                return 1;
            }
        }
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
