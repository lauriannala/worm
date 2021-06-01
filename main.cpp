#include <SDL2/SDL.h>
#include "include/config.h"
#include "worm.h"

int main(int, char**)  {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
            "Worm",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH * WINDOW_MULTIPLIER,
            HEIGHT * WINDOW_MULTIPLIER,
            SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(
            window, -1, SDL_TEXTUREACCESS_TARGET
            );

    auto worm = new Worm(WIDTH / 2, HEIGHT / 2, 3);

    bool running = true;
    while(true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }
        if (!running) break;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect r;

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < WIDTH; y++) {
                if (!worm->is_set(x, y)) continue;

                r.x = x * WINDOW_MULTIPLIER;
                r.y = y * WINDOW_MULTIPLIER;
                r.w = WINDOW_MULTIPLIER;
                r.h = WINDOW_MULTIPLIER;
                SDL_RenderFillRect(renderer, &r);
            }
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    return 0;
}
