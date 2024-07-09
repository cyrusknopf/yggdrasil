#include "game/chess.h"
#include "game/inits.h"
#include "utils.h"
#include <utility>

std::pair<std::array<bitboard, 6>, std::array<bitboard, 6>> initGame() {
    /* utils.h contains the 64 bit start state of each white piece.
     * Reversing these gives the black piece start states.
     */
    std::array<bitboard, 6> whiteBitboards = {whitePawnInit,   whiteHorseInit,
                                              whiteCastleInit, whiteBishopInit,
                                              whiteQueenInit,  whiteKingInit};

    // TODO Change these to contants
    std::array<bitboard, 6> blackBitboards = {blackPawnInit,   blackHorseInit,
                                              blackCastleInit, blackBishopInit,
                                              blackQueenInit,  blackKingInit};

    return std::make_pair(whiteBitboards, blackBitboards);
}

bitboard getGameState(std::array<bitboard, 6> whiteState,
                      std::array<bitboard, 6> blackState) {
    return getGameState(whiteState, blackState, true) |
           getGameState(whiteState, blackState, false);
}

bitboard getGameState(std::array<bitboard, 6> whiteState,
                      std::array<bitboard, 6> blackState, bool colour) {
    bitboard state = 0;
    if (colour) {
        for (auto &board : whiteState) {
            state |= board;
        }
    } else {
        for (auto &board : blackState) {
            state |= board;
        }
    }
    return state;
}

bitboard getTeamState(team &pieces) {
    bitboard state = 0;
    for (auto &piece : pieces) {
        state |= piece;
    }
    return state;
}
