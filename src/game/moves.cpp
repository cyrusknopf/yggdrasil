#include "game/moves.h"
#include "game/chess.h"
#include "utils.h"
#include <array>
#include <vector>

// TODO Include en passant
std::vector<bitboard> pawnPseudoLegalMoves(bitboard ownState, bitboard oppState,
                                           bitboard state, bool colour) {
    std::vector<bitboard> moves;
    bitboard move;
    bitboard both = ownState | oppState;

    if (colour) {
        for (auto &piece : getAllPieces(state)) {
            move = slideNorth(piece);
            if ((move & both) == 0) {
                moves.push_back(move | state & ~piece);
            }

            // If in rank 2 (i.e. starting rank)
            if (piece > 255 && piece < 65536) {
                move = slideNorth(move);
                if ((move & both) == 0) {
                    moves.push_back(move | state & ~piece);
                }
            }

            move = slideNorth(slideEast(piece));
            if ((move & ownState) == 0 && (move & oppState) != 0) {
                moves.push_back(move | state & ~piece);
            }

            move = slideNorth(slideWest(piece));
            if ((move & ownState) == 0 && (move & oppState) != 0) {
                moves.push_back(move | state & ~piece);
            }
        }

    } else {
        for (auto &piece : getAllPieces(state)) {
            move = slideSouth(piece);
            if ((move & both) == 0) {
                moves.push_back(move | state & ~piece);
            }

            // If in rank 7 (i.e. starting rank)
            if (piece > 140737488355328 && piece < 72057594037927936) {
                move = slideSouth(move);
                if ((move & both) == 0) {
                    moves.push_back(move | state & ~piece);
                }
            }

            move = slideSouth(slideEast(piece));
            if ((move & ownState) == 0 && (move & oppState) != 0) {
                moves.push_back(move | state & ~piece);
            }

            move = slideSouth(slideWest(piece));
            if ((move & ownState) == 0 && (move & oppState) != 0) {
                moves.push_back(move | state & ~piece);
            }
        }
    }

    return moves;
};

std::vector<bitboard> horsePseudoLegalMoves(bitboard own, bitboard opp,
                                            bitboard state) {

    bitboard move;
    std::vector<bitboard> moves;

    std::vector<bitboard> pieces = getAllPieces(state);

    for (auto &piece : pieces) {

        move = slideEast(piece);
        move = slideNorth(move);
        move = slideNorth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }

        move = slideNorth(piece);
        move = slideEast(move);
        move = slideEast(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }

        move = slideSouth(piece);
        move = slideEast(move);
        move = slideEast(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }

        move = slideEast(piece);
        move = slideSouth(move);
        move = slideSouth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }

        move = slideWest(piece);
        move = slideSouth(move);
        move = slideSouth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }

        move = slideSouth(piece);
        move = slideWest(move);
        move = slideWest(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }

        move = slideNorth(piece);
        move = slideWest(move);
        move = slideWest(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }

        move = slideWest(piece);
        move = slideNorth(move);
        move = slideNorth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move | state & ~piece);
        }
    }

    return moves;
}

std::vector<bitboard>
castlePseudoLegalMoves(bitboard ownState, bitboard oppState, bitboard state) {

    bitboard move;
    std::vector<bitboard> moves;

    std::vector<bitboard> pieces = getAllPieces(state);

    for (auto &piece : pieces) {

        // Slide north
        move = piece;
        while (slideNorth(move) != 0) {
            move = slideNorth(move);
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }

        // Slide east
        move = piece;
        while (slideEast(move) != 0) {
            move = slideEast(move);
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }

        // Slide south
        move = piece;
        while (slideSouth(move) != 0) {
            move = slideSouth(move);
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }

        // Slide west
        move = piece;
        while (slideWest(move) != 0) {
            move = slideWest(move);
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }
    }
    return moves;
};

std::vector<bitboard>
bishopPseudoLegalMoves(bitboard ownState, bitboard oppState, bitboard state) {

    bitboard move;
    std::vector<bitboard> moves;

    std::vector<bitboard> pieces = getAllPieces(state);

    for (auto &piece : pieces) {

        // Slide north east
        move = piece;
        while (slideNorth(slideEast(move)) != 0) {
            move = slideNorth(slideEast(move));
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }

        // Slide south east
        move = piece;
        while (slideSouth(slideEast(move)) != 0) {
            move = slideSouth(slideEast(move));
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }

        // Slide south west
        move = piece;
        while (slideSouth(slideWest(move)) != 0) {
            move = slideSouth(slideWest(move));
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }

        // Slide north west
        move = piece;
        while (slideNorth(slideWest(move)) != 0) {
            move = slideNorth(slideWest(move));
            if ((move & ownState) != 0) {
                break;
            }
            moves.push_back(move | state & ~piece);
            if ((move & oppState) != 0) {
                break;
            }
        }
    }
    return moves;
};

std::vector<bitboard> queenPseudoLegalMoves(bitboard ownState,
                                            bitboard oppState, bitboard state) {
    std::vector<bitboard> moves;

    for (auto &piece : getAllPieces(state)) {

        std::vector<bitboard> diagonals =
            bishopPseudoLegalMoves(ownState, oppState, state);
        std::vector<bitboard> straights =
            castlePseudoLegalMoves(ownState, oppState, state);

        for (auto &move : diagonals) {
            moves.push_back(move | state & ~piece);
        }

        for (auto &move : straights) {
            moves.push_back(move | state & ~piece);
        }
    }

    return moves;
};

std::vector<bitboard> kingPseudoLegalMoves(bitboard ownState, bitboard oppState,
                                           bitboard state) {

    bitboard move;
    std::vector<bitboard> moves;

    move = slideNorth(state);
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    move = slideNorth(slideEast(state));
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    move = slideEast(state);
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    move = slideSouth(slideEast(state));
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    move = slideSouth(state);
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    move = slideSouth(slideWest(state));
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    move = slideWest(state);
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    move = slideNorth(slideWest(state));
    if (move != 0 && (move & ownState) == 0) {
        moves.push_back(move);
    }

    return moves;
}

std::vector<bitboard> pseudoLegalFromIndex(int idx, team &white, team &black,
                                           bool colour) {
    bitboard ownState;
    bitboard oppState;
    team thisTeam;
    if (colour) {
        ownState = getGameState(white, black, true);
        oppState = getGameState(white, black, false);
        thisTeam = white;
    } else {
        ownState = getGameState(white, black, false);
        oppState = getGameState(white, black, true);
        thisTeam = black;
    }

    switch (idx) {
    case 0:
        return pawnPseudoLegalMoves(ownState, oppState, thisTeam.at(idx),
                                    colour);
    case 1:
        return horsePseudoLegalMoves(ownState, oppState, thisTeam.at(idx));
    case 2:
        return castlePseudoLegalMoves(ownState, oppState, thisTeam.at(idx));
    case 3:
        return bishopPseudoLegalMoves(ownState, oppState, thisTeam.at(idx));
    case 4:
        return queenPseudoLegalMoves(ownState, oppState, thisTeam.at(idx));
    case 5:
        return kingPseudoLegalMoves(ownState, oppState, thisTeam.at(idx));
    default:
        return std::vector<bitboard>{};
    }
}
