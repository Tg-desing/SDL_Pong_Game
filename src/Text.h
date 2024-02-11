#include <SDL2/SDL2_TTF/SDL_ttf.h>
#include <SDL2/SDL.h>

class SDL_TextTexture
{
    public:
        SDL_TextTexture();
        ~SDL_TextTexture();
        void RenderText(SDL_Renderer *gRenderer, TTF_Font *gFont, const char *text, SDL_Color color, int x, int y);

    private:
        SDL_Texture *createTextTexture(SDL_Renderer *gRenderer, TTF_Font *gFont, const char *text, SDL_Color color);




};