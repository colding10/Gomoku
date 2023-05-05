#include "eventhandler.h"

#include <SDL.h>

#include "gomolib.h"
#include "main.h"

extern SDL_Window* window;

void handleMouseClicked(SDL_MouseButtonEvent event, gomolib::Board& board) {
    if (event.button == SDL_BUTTON_RIGHT) {
        return;
    }

    gomolib::Position board_location = getBoardIndices(event.x, event.y);
    if (board.isPosEmpty(board_location)) {
        board.setPieceAt(board_location, board.getTurn());
        board.makeMove();
    }
}

gomolib::Position getBoardIndices(int x, int y) {
    int row = static_cast<int>(std::round((y - BORDER_PX) / static_cast<double>(GRID_TILE_PX)));
    int col = static_cast<int>(std::round((x - BORDER_PX) / static_cast<double>(GRID_TILE_PX)));
    return gomolib::Position(col, row);
}
