#include <cctype>
#include <climits>
#include <iostream>

#include "gomolib.h"

#define INF std::numeric_limits<int>::max()
#define NEG_INF std::numeric_limits<int>::min()

int alpha_beta_minimax(gomolib::Board& board, int depth, int alpha, int beta, bool is_max_player) {
    if (depth == 0 || board.wasWinningMove()) {
        return board.evaluate(is_max_player);  // evaluate the board position
    }

    if (is_max_player) {
        int best_score = NEG_INF;
        for (auto move : board.getLegalMoves()) {
            board.makeMove(move);
            int score = alpha_beta_minimax(board, depth - 1, alpha, beta, false);
            board.undoMove();
            best_score = std::max(best_score, score);
            alpha = std::max(alpha, best_score);
            if (beta <= alpha) {
                break;  // beta cut-off
            }
        }
        return best_score;
    } else {
        int best_score = INF;
        for (auto move : board.getLegalMoves()) {
            board.makeMove(move);
            int score = alpha_beta_minimax(board, depth - 1, alpha, beta, true);
            board.undoMove();
            best_score = std::min(best_score, score);
            beta = std::min(beta, best_score);
            if (beta <= alpha) {
                break;  // alpha cut-off
            }
        }
        return best_score;
    }
}

gomolib::Position findBestMove(gomolib::Board& board, int depth) {
    int best_score = NEG_INF;
    gomolib::Position best_move;

    bool is_max_player = board.getTurn() == gomolib::Color::WHITE;

    for (auto move : board.getLegalMoves()) {
        board.makeMove(move);
        int score = alpha_beta_minimax(board, depth - 1, NEG_INF, INF, !is_max_player);
        board.undoMove();
        if (is_max_player && score > best_score) {
            best_score = score;
            best_move = move;
        } else if (!is_max_player && score < best_score) {
            best_score = score;
            best_move = move;
        }
    }
    return best_move;
}
