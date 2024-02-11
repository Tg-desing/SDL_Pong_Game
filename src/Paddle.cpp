#include <SDL2/SDL.h>
#include "Paddle.h"

Paddle::Paddle(int playerNum) : x(50), y(10), w(20), h(100), playerNum(playerNum) {}

Paddle::~Paddle() {}

void Paddle::Init()
{
    if (playerNum == 1)
        x = 50;
    else
        x = 750;
}
void Paddle::UpdatePosY(int direction)
{
    // direction 1 is up, -1 is down
    if (direction == 1)
        y += 10;
    else
        y -= 10;
}

void Paddle::Render(SDL_Renderer *pRenderer)
{
    SDL_Rect paddle = {x, y, w, h};
    SDL_RenderDrawRect(pRenderer, &paddle);
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pRenderer, &paddle);
}