#ifndef GOMOLIB_TYPES_H
#define GOMOLIB_TYPES_H

namespace gomolib {
enum class Color { BLACK,
                   WHITE,
                   NOCOLOR };

struct Position {
    int row;
    int col;

    Position(int r, int c) : row(r), col(c) {}
    Position() : row(0), col(0) {}
    
    inline bool operator==(const Position &other) {
        return other.row == this->row && other.col == this->col;
    }
};

inline Color getOppositeColor(Color &color) {
    return static_cast<Color>(static_cast<int>(color) ^ 1);
}

}  // namespace gomolib
#endif