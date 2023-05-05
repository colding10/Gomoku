#ifndef GOMOGUI_COLORS_H
#define GOMOGUI_COLORS_H

#include <SDL.h>

#include "gomolib.h"

constexpr SDL_Color CL_WHITE = {255, 255, 255, 255};
constexpr SDL_Color CL_BLACK = {0, 0, 0, 255};

constexpr SDL_Color GRID_BACKGROUND = {190, 150, 90, 255};  // Beigeish
constexpr SDL_Color GRID_LINE_COLOR = {19, 22, 22, 255};    // Barely Black

inline SDL_Color getColor(const gomolib::Color& c) {
    switch (c) {
        case gomolib::Color::WHITE:
            return CL_WHITE;
        case gomolib::Color::BLACK:
            return CL_BLACK;
        default:
            std::cout << (int)c << std::endl;
            throw std::invalid_argument("received color that was not white or black");
    }
}

#endif