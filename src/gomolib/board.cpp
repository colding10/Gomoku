#include "board.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

#include "types.h"

namespace gomolib {

int Board::evaluate(bool is_max_player) const {
    if (this->wasWinningMove()) {
        return std::numeric_limits<int>::max() * (is_max_player ? -1 : 1);
    }

    int score = 0;

    // Check rows
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size - 4; x++) {
            int black_count = 0;
            int white_count = 0;
            for (int i = 0; i < 5; i++) {
                if (cells_[x + i][y] == Color::BLACK) {
                    black_count++;
                } else if (cells_[x + i][y] == Color::WHITE) {
                    white_count++;
                }
            }
            if (black_count > 0 && white_count == 0) {
                score += std::pow(10, black_count);
            } else if (white_count > 0 && black_count == 0) {
                score -= std::pow(10, white_count);
            }
        }
    }

    // Check columns
    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size - 4; y++) {
            int black_count = 0;
            int white_count = 0;
            for (int i = 0; i < 5; i++) {
                if (cells_[x][y + i] == Color::BLACK) {
                    black_count++;
                } else if (cells_[x][y + i] == Color::WHITE) {
                    white_count++;
                }
            }
            if (black_count > 0 && white_count == 0) {
                score += std::pow(10, black_count);
            } else if (white_count > 0 && black_count == 0) {
                score -= std::pow(10, white_count);
            }
        }
    }

    // Check diagonals
    for (int x = 0; x < board_size - 4; x++) {
        for (int y = 0; y < board_size - 4; y++) {
            int black_count = 0;
            int white_count = 0;
            for (int i = 0; i < 5; i++) {
                if (cells_[x + i][y + i] == Color::BLACK) {
                    black_count++;
                } else if (cells_[x + i][y + i] == Color::WHITE) {
                    white_count++;
                }
            }
            if (black_count > 0 && white_count == 0) {
                score += std::pow(10, black_count);
            } else if (white_count > 0 && black_count == 0) {
                score -= std::pow(10, white_count);
            }
        }
    }

    for (int x = 4; x < board_size; x++) {
        for (int y = 0; y < board_size - 4; y++) {
            int black_count = 0;
            int white_count = 0;
            for (int i = 0; i < 5; i++) {
                if (cells_[x - i][y + i] == Color::BLACK) {
                    black_count++;
                } else if (cells_[x - i][y + i] == Color::WHITE) {
                    white_count++;
                }
            }
            if (black_count > 0 && white_count == 0) {
                score += std::pow(10, black_count);
            } else if (white_count > 0 && black_count == 0) {
                score -= std::pow(10, white_count);
            }
        }
    }

    return score * (is_max_player ? -1 : 1);
}

void Board::makeMove(const Position& p) {
    this->setPieceAt(p, this->getTurn());
    this->makeMove();
}

void Board::makeMove() {
    turn = getOppositeColor(this->turn);
}

void Board::undoMove() {
    cells_[this->placed_history.back().row][this->placed_history.back().col] = Color::NOCOLOR;
    turn = getOppositeColor(this->turn);
    this->placed_history.pop_back();
}

std::vector<Position> Board::getLegalMoves() {
    std::vector<Position> out;

    for (int i = 0; i < this->board_size; i++) {
        for (int j = 0; j < this->board_size; j++) {
            if (this->isPosEmpty({i, j})) {
                out.push_back(Position(i, j));
            }
        }
    }

    return out;
}

bool Board::wasWinningMove() const {
    Position last_pos = this->placed_history.back();
    Color checking_color = this->getCellAt(last_pos);
    int count = 0;

    // Check horizontally
    for (int x = last_pos.row - 4; x <= last_pos.row + 4; x++) {
        if (x < 0 || x >= this->board_size) {
            continue;
        }
        if (this->getCellAt(Position(x, last_pos.col)) == checking_color) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    // Check vertically
    count = 0;
    for (int y = last_pos.col - 4; y <= last_pos.col + 4; y++) {
        if (y < 0 || y >= this->board_size) {
            continue;
        }
        if (this->getCellAt(Position(last_pos.row, y)) == checking_color) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    // Check diagonally (top-left to bottom-right)
    count = 0;
    for (int i = -4; i <= 4; i++) {
        int x = last_pos.row + i;
        int y = last_pos.col + i;
        if (x < 0 || x >= this->board_size || y < 0 || y >= this->board_size) {
            continue;
        }
        if (this->getCellAt(Position(x, y)) == checking_color) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    // Check diagonally (bottom-left to top-right)
    count = 0;
    for (int i = -4; i <= 4; i++) {
        int x = last_pos.row + i;
        int y = last_pos.col - i;
        if (x < 0 || x >= this->board_size || y < 0 || y >= this->board_size) {
            continue;
        }
        if (this->getCellAt(Position(x, y)) == checking_color) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else {
            count = 0;
        }
    }

    return false;
}

Color Board::getTurn() const {
    return this->turn;
}

bool Board::isPosEmpty(const Position& pos) const {
    if (pos.row < 0 || pos.row >= this->board_size || pos.col < 0 || pos.col >= this->board_size) {
        throw std::invalid_argument("pos indexes are out of range");
    }

    return this->cells_[pos.row][pos.col] == Color::NOCOLOR;
}

void Board::setPieceAt(const Position& pos, const Color& state) {
    if (pos.row < 0 || pos.row >= this->board_size || pos.col < 0 || pos.col >= this->board_size) {
        throw std::invalid_argument("pos indexes are out of range");
    }

    cells_[pos.row][pos.col] = state;
    this->placed_history.push_back(pos);
}

Color Board::getCellAt(const Position& pos) const {
    if (pos.row < 0 || pos.row >= this->board_size || pos.col < 0 || pos.col >= this->board_size) {
        throw std::invalid_argument("pos indexes are out of range");
    }

    return this->cells_[pos.row][pos.col];
}

bool Board::isBoardFull() const {
    for (int i = 0; i < this->board_size; i++) {
        for (int j = 0; j < this->board_size; j++) {
            if (cells_[i][j] == Color::NOCOLOR) {
                return false;
            }
        }
    }
    return true;
}

void Board::printBoard() const {
    for (int i = 0; i < this->board_size; i++) {
        for (int j = 0; j < this->board_size; j++) {
            switch (cells_[i][j]) {
                case Color::NOCOLOR:
                    std::cout << ".";
                    break;
                case Color::BLACK:
                    std::cout << "X";
                    break;
                case Color::WHITE:
                    std::cout << "O";
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
}  // namespace gomolib