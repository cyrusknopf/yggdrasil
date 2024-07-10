#include "game/moves.h"
#include "game/chess.h"
#include "utils.h"
#include <array>
#include <iostream>
#include <vector>

/*
 * I opt to not use an array of function pointers for carrying out moves due to
 * the apparent inability of the compiler to perform function inlining.
 * Whether this is true or not, I am not sure, but I feel the readability of the
 * code does not suffer and possibly is even more readable when explicitly
 * listing moves.
 */

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
        move = state;
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

        // Slide south
        move = state;
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

        // Slide east
        move = state;
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

        // Slide west
        move = state;
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
        move = state;
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
        move = state;
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
        move = state;
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
        move = state;
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

std::vector<bitboard> allPseudoLegalMoves(std::array<bitboard, 6> &own,
                                          std::array<bitboard, 6> &opp,
                                          bool colour) {
    std::vector<bitboard> moves;

    // XXX ref to array

    bitboard ownState = getGameState(own, opp, true);
    bitboard oppState = getGameState(own, opp, false);

    bitboard pawns = own.at(0);
    bitboard horses = own.at(1);
    bitboard castles = own.at(2);
    bitboard bishops = own.at(3);
    bitboard queens = own.at(4);
    bitboard king = own.at(5);

    std::vector<bitboard> pawnMoves =
        pawnPseudoLegalMoves(ownState, oppState, pawns, colour);

    std::vector<bitboard> horseMoves =
        horsePseudoLegalMoves(ownState, oppState, horses);

    std::vector<bitboard> castleMoves =
        castlePseudoLegalMoves(ownState, oppState, castles);

    std::vector<bitboard> bishopMoves =
        bishopPseudoLegalMoves(ownState, oppState, bishops);

    std::vector<bitboard> queenMoves =
        queenPseudoLegalMoves(ownState, oppState, queens);

    std::vector<bitboard> kingMoves =
        kingPseudoLegalMoves(ownState, oppState, king);

    moves.insert(moves.end(), pawnMoves.begin(), pawnMoves.end());
    moves.insert(moves.end(), horseMoves.begin(), horseMoves.end());
    moves.insert(moves.end(), castleMoves.begin(), castleMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    moves.insert(moves.end(), queenMoves.begin(), queenMoves.end());
    moves.insert(moves.end(), kingMoves.begin(), kingMoves.end());

    return moves;
}

std::vector<bitboard> pseudoLegalFromIndex(int idx,
                                           std::array<bitboard, 6> &own,
                                           std::array<bitboard, 6> &opp,
                                           bool colour) {
    bitboard ownState = getGameState(own, opp, true);
    std::cout << "ownstate " << ownState << std::endl;
    bitboard oppState = getGameState(own, opp, false);
    std::cout << "oppstate" << oppState << std::endl;

    std::cout << "own.at(idx)" << own.at(idx) << std::endl;

    switch (idx) {
    case 0:
        return pawnPseudoLegalMoves(ownState, oppState, own.at(idx), colour);
    case 1:
        return horsePseudoLegalMoves(ownState, oppState, own.at(idx));
    case 2:
        return castlePseudoLegalMoves(ownState, oppState, own.at(idx));
    case 3:
        return bishopPseudoLegalMoves(ownState, oppState, own.at(idx));
    case 4:
        return queenPseudoLegalMoves(ownState, oppState, own.at(idx));
    case 5:
        return kingPseudoLegalMoves(ownState, oppState, own.at(idx));
    default:
        return std::vector<bitboard>{};
    }
}
