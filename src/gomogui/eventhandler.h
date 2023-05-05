#ifndef GOMOGUI_EVENTHANDLER_H
#define GOMOGUI_EVENTHANDLER_H

#include <SDL.h>

#include "gomolib.h"

void handleMouseClicked(SDL_MouseButtonEvent event, gomolib::Board& board);
gomolib::Position getBoardIndices(int x, int y);

#endif