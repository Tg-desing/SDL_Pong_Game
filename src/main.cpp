#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
#include <SDL2/SDL2_TTF/SDL_ttf.h>

#undef main

int main()
{
        SDL_Window *pWindow = NULL;
        SDL_Renderer *pRenderer = NULL;
        TTF_Font *pFont = NULL;

        Game *game = Game::GetInstance();
        int initComplte = game->init(pWindow, pRenderer, pFont);
        if (initComplte == 0)
        {
                printf("Init failed");
                return 0;
        }
        game->Render(pRenderer, pFont);
        game->Run(pRenderer);
}