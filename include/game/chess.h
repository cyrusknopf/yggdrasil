#include "utils.h"
#include <array>
#include <utility>

/*
 * Contains the main logic of the game of chess.
 */

std::pair<std::array<bitboard, 6>, std::array<bitboard, 6>> initGame();

bitboard getGameState(std::array<bitboard, 6> whiteState,
                      std::array<bitboard, 6> blackState);

bitboard getGameState(std::array<bitboard, 6> whiteState,
                      std::array<bitboard, 6> blackState, bool colour);
