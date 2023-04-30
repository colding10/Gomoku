#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <SDL2/SDL.h>

#include "gomolib.h"

constexpr int GRID_TILE_PX = 50;
constexpr int BORDER_PX = 30;
constexpr int CIRCLE_RADIUS_PX = 18;

constexpr int GRID_WIDTH = 19;
constexpr int GRID_HEIGHT = GRID_WIDTH;

constexpr int WINDOW_WIDTH_PX = ((GRID_WIDTH - 1) * GRID_TILE_PX) + BORDER_PX * 2;
constexpr int WINDOW_HEIGHT_PX = ((GRID_HEIGHT - 1) * GRID_TILE_PX) + BORDER_PX * 2;

void drawGrid(SDL_Renderer& renderer, const gomolib::Board& board);
void clearScreen(SDL_Renderer& renderer);
void handleMouseClicked(SDL_MouseButtonEvent event, gomolib::Board& board);

gomolib::Position getBoardIndices(int x, int y);

#endif  // !MAIN_H_INCLUDED