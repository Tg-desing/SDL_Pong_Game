#ifndef PADDLEH
#define PADDLEH

#include <SDL2/SDL.h>

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

public:
    void Init();
    void UpdatePosY(int direction);
    void Render(SDL_Renderer *pRenderer);

public:
    int playerNum;
};

#endif