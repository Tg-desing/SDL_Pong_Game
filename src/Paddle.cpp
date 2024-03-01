#include <SDL2/SDL.h>
#include "Paddle.h"

extern int WIDTH;
extern int HEIGHT;

Paddle::Paddle(int playerNum) : x(50), y((HEIGHT / 2)), w(20), h(100), playerNum(playerNum) {}

Paddle::~Paddle() {}

void Paddle::Init()
{
    if (playerNum == 1)
        x = 50;
    else
        x = WIDTH - 50 - w;
}
void Paddle::UpdatePosY(int direction, int dt)
{
    // direction 1 is up, -1 is down
    if (direction == 1)
    {
        if (y <= (HEIGHT - h))
            y += velocity * dt;
    }
    else
    {
        if (y >= 0)
            y -= velocity * dt;
    }
}

void Paddle::Render(SDL_Renderer *pRenderer)
{
    SDL_Rect paddle = {x, y, w, h};
    SDL_RenderDrawRect(pRenderer, &paddle);
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pRenderer, &paddle);
}