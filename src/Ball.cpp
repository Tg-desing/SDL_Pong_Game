#include "Ball.h"
#include "Vec2.h"

float Ball::DIRECTION[2] = {1.0f, -1.0f};
Ball::Ball(Vec2 ballPos) : pos(ballPos) {}

void Ball::Init()
{
    velocity.x = 2.0f;
    velocity.y = 1.5f;
}

void Ball::UpdatePos()
{
    pos += velocity * DIRECTION[0];
}

void Ball::Render(SDL_Renderer *pRenderer)
{
    SDL_Rect ball = {(int)pos.x, (int)pos.y, 20, 20};
    SDL_RenderDrawRect(pRenderer, &ball);
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pRenderer, &ball);
}
