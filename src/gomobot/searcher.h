#ifndef GOMOBOT_SEARCHER_H
#define GOMOBOT_SEARCHER_H

#include <cctype>
#include <climits>
#include <iostream>

#include "gomolib.h"

gomolib::Position findBestMove(gomolib::Board& board, int depth);
int alpha_beta_minimax(gomolib::Board& board, int depth, int alpha, int beta, bool is_max_player);

#endif