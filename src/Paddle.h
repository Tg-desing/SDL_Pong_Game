#ifndef PADDLEH
#define PADDLEH

#include <SDL2/SDL.h>
#include "Vec2.h"

class Paddle
{
public:
    Paddle(int playerNum);
    ~Paddle();

private:
    int x;
    int y;
    int w;
    int h;
    float velocity = 0.5f;

public:
    void Init();
    void UpdatePosY(int direction, int dt);
    void Render(SDL_Renderer *pRenderer);

public:
    Vec2 GetPos()
    {
        return Vec2(x, y);
    }

    Vec2 GetSize()
    {
        return Vec2(w, h);
    }

    int GetPlayerNum()
    {
        return playerNum;
    }

public:
    int playerNum;
};

#endif