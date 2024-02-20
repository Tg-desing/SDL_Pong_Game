#include <SDL2/SDL.h>
#include <SDL2/SDL2_TTF/SDL_ttf.h>
#include "GameProcess.h"
#include "Ball.h"

class Game
{
private:
    static Game *instance;
    Game();
    ~Game();

public:
    static Game *GetInstance();
    bool init(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *&pFont);
    void Render(SDL_Renderer *pRenderer, TTF_Font *pFont);
    void Run(SDL_Renderer *pRenderer);

public:
    static int lastticks;
    static int curticks;
    static float fps;
    static int framecount;
    static SDL_Event event;
    static int done;

private:
    GameProcess *gameProcess;
    Ball *pBall;
};