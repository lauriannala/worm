#include <SDL2/SDL.h>
#include <thread>
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

    Worm worm(WIDTH / 2, HEIGHT / 2, 3);

    bool running = true;

    bool game_tick;
    int game_tick_counter = 0;
    int game_tick_schedule = 200;

    while(true) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                auto key = event.key.keysym.sym;
                switch (key) {
                    case SDLK_UP:
                        worm.set_direction(UP);
                        break;
                    case SDLK_DOWN:
                        worm.set_direction(DOWN);
                        break;
                    case SDLK_RIGHT:
                        worm.set_direction(RIGHT);
                        break;
                    case SDLK_LEFT:
                        worm.set_direction(LEFT);
                        break;
                    default:
                        break;
                }
                break;
            }
        }
        if (!running) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (game_tick_schedule != 0) {
            game_tick_schedule -= 100;
            game_tick = false;
        } else {
            game_tick_counter++;
            game_tick_schedule = 200;
            game_tick = true;
        }

        if (!game_tick) continue;

        printf("game tick %i \n", game_tick_counter);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect r;

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < WIDTH; y++) {
                if (!worm.is_set(x, y)) continue;

                r.x = x * WINDOW_MULTIPLIER;
                r.y = y * WINDOW_MULTIPLIER;
                r.w = WINDOW_MULTIPLIER;
                r.h = WINDOW_MULTIPLIER;
                SDL_RenderFillRect(renderer, &r);
            }
        }
        SDL_RenderPresent(renderer);

        worm.move();
    }

    SDL_DestroyWindow(window);
    return 0;
}
