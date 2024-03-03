#include "enum.h"
#include "Ball.h"
#include <cmath>
#include <stdio.h>
#include "Vec2.h"
#include "Paddle.h"
#include "Game.h"
using namespace std;

extern int BALLWIDTH;
extern int BALLHEIGHT;
extern int HEIGHT;
Ball::Ball(Vec2 ballPos) : velocity(10.0f), pos(ballPos), bounceAngle(0.0f), DIRECTION(Vec2(1.0f, 0.0f)), collideType(wallCollideType::NONE), firstCollide(false) {}
Ball::~Ball() {}

void Ball::Init(WINSIDE winSide)
{
    if (winSide == WINSIDE::LEFT)
        DIRECTION = {-1.0f, 0.0f};
    else if (winSide == WINSIDE::RIGHT)
        DIRECTION = {1.0f, 0.0f};
    else
        DIRECTION = {1.0f, 0.0f};
}

void Ball::UpdatePos(Paddle **pPaddles)
{
    if (firstCollide)
        velocity = 15.0f;

    if (IsWallCollide())
    {
        if (collideType == wallCollideType::TOP)
        {
            DIRECTION.y = 1.0f;
        }
        else if (collideType == wallCollideType::BOTTOM)
        {
            DIRECTION.y = -1.0f;
        }
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
    pos += DIRECTION * velocity;
}

bool Ball::IsWallCollide()
{
    if (pos.y >= HEIGHT - BALLHEIGHT)
    {
        collideType = wallCollideType::BOTTOM;
        return true;
    }
    else if (pos.y <= 0)
    {
        collideType = wallCollideType::TOP;
        return true;
    }
    return false;
}

int Ball::IsPaddleCollide(Paddle *paddle)
{

    Vec2 paddlePos = paddle->GetPos();
    Vec2 paddleSize = paddle->GetSize();

    if (paddle->GetPlayerNum() == 1)
    {
        float minCollidePosY = paddlePos.y - (float)BALLHEIGHT;
        float maxCollidePosY = paddlePos.y + paddleSize.y;

        if (pos.y <= maxCollidePosY && pos.y >= minCollidePosY)
        {
            if (pos.x <= (paddlePos.x + paddleSize.x) && pos.x > paddlePos.x)
            {
                if (!firstCollide)
                    firstCollide = true;

                float relativeIntersectY = (paddlePos.y + paddleSize.y / 2) - pos.y;
                float normalizedRelativeIntersectY = relativeIntersectY / (paddleSize.y / 2);
                bounceAngle = normalizedRelativeIntersectY * 75.0f;
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
                if (!firstCollide)
                    firstCollide = true;

                float relativeIntersectY = (paddlePos.y + paddleSize.y / 2) - pos.y;
                float normalizedRelativeIntersectY = relativeIntersectY / (paddleSize.y / 2);
                bounceAngle = normalizedRelativeIntersectY * 75.0f;
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
