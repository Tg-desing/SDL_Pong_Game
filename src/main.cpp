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
        TTF_Font *pTextFont = NULL;
        TTF_Font *pScoreFont = NULL;

        Game *game = Game::GetInstance();
        int initComplte = game->init(pWindow, pRenderer, pTextFont, pScoreFont);
        if (initComplte == 0)
        {
                printf("Init failed");
                return 0;
        }
        game->Render(pRenderer, pTextFont);
        game->Run(pRenderer, pScoreFont);
}