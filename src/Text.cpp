#include <stdio.h>
#include "Text.h"
#include <SDL2/SDL2_TTF/SDL_ttf.h>

SDL_TextTexture::SDL_TextTexture() {} 

SDL_TextTexture::~SDL_TextTexture() {}

SDL_Texture *SDL_TextTexture::createTextTexture(SDL_Renderer *gRenderer, TTF_Font *gFont, const char *text, SDL_Color color)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text, color);

    if (textSurface == nullptr)
    {
        printf("Error making text surface");
        return nullptr;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    if (textTexture == nullptr)
    {
        printf("Error making text texture");
        return nullptr;
    }

    SDL_FreeSurface(textSurface);
    return textTexture;
}

void SDL_TextTexture::RenderText(SDL_Renderer *gRenderer, TTF_Font *gFont, const char *text, SDL_Color color, int x, int y)
{
    SDL_Texture *textTexture = createTextTexture(gRenderer, gFont, text, color);
    if (textTexture == nullptr)
    {
        return;
    }
    SDL_Rect renderQuad = {x, y, 0, 0};
    SDL_QueryTexture(textTexture, NULL, NULL, &renderQuad.w, &renderQuad.h);
    SDL_RenderCopy(gRenderer, textTexture, NULL, &renderQuad);
    SDL_DestroyTexture(textTexture);
}