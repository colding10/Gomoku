#ifndef GOMOLIB_BOARD_H
#define GOMOLIB_BOARD_H

#include <iostream>
#include <vector>

#include "types.h"

namespace gomolib {
class Board {
   public:
    Board() {
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 19; j++) {
                cells_[i][j] = Color::NOCOLOR;
            }
        }

        turn = Color::BLACK;
        this->board_size = 19;
    }

    Board(int board_size) {
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                cells_[i][j] = Color::NOCOLOR;
            }
        }

        turn = Color::BLACK;
        this->board_size = board_size;
    }

    Color getTurn() const;

    bool wasWinningMove() const;

    bool isPosEmpty(const Position &pos) const;

    void setPieceAt(const Position &pos, const Color &state);

    void makeMove();
    void makeMove(const Position &p);

    void undoMove();

    Color getCellAt(const Position &pos) const;

    bool isBoardFull() const;

    void printBoard() const;

    int getBoardSize() const { return this->board_size; }
    int evaluate(bool is_max_player) const;

    std::vector<Position> getLegalMoves();

   private:
    int board_size;
    std::vector<Position> placed_history;

    Color cells_[100][100];  // maximum size of 100x100
    Color turn;
};
}  // namespace gomolib

#endif