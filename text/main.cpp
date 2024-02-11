#include <SDL2/SDL.h>
#include <iostream>

#undef main
int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 창 생성
    SDL_Window* window = SDL_CreateWindow("SDL 예제", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "창 생성 실패: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 3초 동안 창 표시
    SDL_Delay(3000);

    // 리소스 해제 및 SDL 종료
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
