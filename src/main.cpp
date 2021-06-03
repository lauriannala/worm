#include <SDL2/SDL.h>
#include <thread>
#include "../include/config.h"
#include "../include/worm.h"
#include "../include/apple.h"

int get_random_coordinate(int min, int max);

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

    Worm worm(WORM_INIT_X, WORM_INIT_Y, WORM_INIT_LENGTH);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    auto apple_x = []() { return get_random_coordinate(0, WIDTH - 1); };
    auto apple_y = []() { return get_random_coordinate(0, HEIGHT - 1); };
    Apple apple(apple_x(), apple_y());

    bool running = true;

    bool game_tick;
    int game_tick_schedule = GAME_TICK_SCHEDULE;
    int score = 0;

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

        std::this_thread::sleep_for(std::chrono::milliseconds(GAME_LOOP_FREQ));

        if (game_tick_schedule != 0) {
            game_tick_schedule -= GAME_TICK_STEP;
            game_tick = false;
        } else {
            game_tick_schedule = GAME_TICK_SCHEDULE;
            game_tick = true;
        }

        if (!game_tick) continue;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_Rect r;

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < WIDTH; y++) {
                if (apple.is_set(x, y) && worm.is_set(x, y)) {
                    worm.grow();
                    apple.reset(apple_x(), apple_y());
                    score += 10;
                    printf("SCORE: %i\n", score);
                }

                if (!worm.is_set(x, y) && !apple.is_set(x, y)) continue;

                if (worm.has_collisions(x, y)) {
                    worm.reset(WORM_INIT_X, WORM_INIT_Y, WORM_INIT_LENGTH);
                    score = 0;
                }

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

int get_random_coordinate(int min, int max) {
    return min + rand() % static_cast<int>(max - min + 1);
}
