#include "main.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <stdexcept>
#include <string>

#include "colors.h"
#include "eventhandler.h"
#include "gomolib.h"
#include "searcher.h"
#include "utils/extradraw.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("gomogui", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    bool gameover = false;

    SDL_Event event;

    gomolib::Board board(GRID_WIDTH);

    bool player_moved = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONUP && !gameover) {
                handleMouseClicked(event.button, board);
                player_moved = true;
            }
        }

        clearScreen(*renderer);
        drawGrid(*renderer, board);

        SDL_RenderPresent(renderer);

        if (player_moved) {
            if (board.wasWinningMove()) {
                std::cout << "you won gg" << std::endl;
                gameover = true;
            }

            gomolib::Position bm = findBestMove(board, 2);

            board.makeMove(bm);
            if (board.wasWinningMove()) {
                std::cout << "the bot won ezpz" << std::endl;
                gameover = true;
            }

            player_moved = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void clearScreen(SDL_Renderer& renderer) {
    SDL_SetRenderDrawColor(&renderer, GRID_BACKGROUND.r, GRID_BACKGROUND.g,
                           GRID_BACKGROUND.b, GRID_BACKGROUND.a);
    SDL_RenderClear(&renderer);
}

void drawGrid(SDL_Renderer& renderer, const gomolib::Board& board) {
    SDL_SetRenderDrawColor(&renderer, GRID_LINE_COLOR.r, GRID_LINE_COLOR.g,
                           GRID_LINE_COLOR.b, GRID_LINE_COLOR.a);

    for (int x = BORDER_PX; x < 1 + GRID_WIDTH * GRID_TILE_PX;
         x += GRID_TILE_PX) {
        SDL_RenderDrawLine(&renderer, x, BORDER_PX, x, WINDOW_HEIGHT_PX - BORDER_PX);
    }

    for (int y = BORDER_PX; y < 1 + GRID_HEIGHT * GRID_TILE_PX;
         y += GRID_TILE_PX) {
        SDL_RenderDrawLine(&renderer, BORDER_PX, y, WINDOW_WIDTH_PX - BORDER_PX, y);
    }

    for (int x = BORDER_PX; x < 1 + GRID_WIDTH * GRID_TILE_PX;
         x += GRID_TILE_PX) {
        int x_index = (x - BORDER_PX) / GRID_TILE_PX;

        for (int y = BORDER_PX; y < 1 + GRID_HEIGHT * GRID_TILE_PX;
             y += GRID_TILE_PX) {
            int y_index = (y - BORDER_PX) / GRID_TILE_PX;

            if (!board.isPosEmpty({x_index, y_index})) {
                SDL_RenderDrawFilledCircle(&renderer, x, y, CIRCLE_RADIUS_PX, getColor(board.getCellAt({x_index, y_index})));
            }
        }
    }
}
