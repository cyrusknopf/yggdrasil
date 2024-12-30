#include "game/moves.h"

#include <array>
#include <random>
#include <utility>
#include <vector>

#include "game/chess.h"
#include "mcts/rollout.h"
#include "utils.h"

// TODO Include en passant
std::vector<bitboard> pawnPseudoLegalMoves(bitboard ownState, bitboard oppState,
                                           bitboard state, bool colour) {
    std::vector<bitboard> moves;
    bitboard move;
    bitboard both = ownState | oppState;

    if (colour) {
        // White pawns
        for (auto& piece : getAllPieces(state)) {
            // Single push
            move = slideNorth(piece);
            if ((move & both) == 0 && move != 0) {
                moves.push_back(move | state & ~piece);

                // If in rank 2 (i.e. starting rank)
                if (piece > 255 && piece < 65536) {
                    // Double push
                    move = slideNorth(move);
                    if ((move & both) == 0 && move != 0) {
                        moves.push_back(move | state & ~piece);
                    }
                }
            }

            // Northeasterly capture
            move = slideNorth(slideEast(piece));
            // No friendly collision and a opp collision
            if ((move & ownState) == 0 && (move & oppState) != 0 && move != 0) {
                moves.push_back(move | state & ~piece);
            }

            // Northwesterly capture
            move = slideNorth(slideWest(piece));
            // No friendly collision and a opp collision
            if ((move & ownState) == 0 && (move & oppState) != 0 && move != 0) {
                moves.push_back(move | state & ~piece);
            }
        }
    } else {
        // Black pawns
        for (auto& piece : getAllPieces(state)) {
            // Single push
            move = slideSouth(piece);
            if ((move & both) == 0 && move != 0) {
                moves.push_back(move | state & ~piece);

                // If in rank 7 (i.e. starting rank)
                if (piece > 140737488355328 && piece < 72057594037927936) {
                    // Double push
                    move = slideSouth(move);
                    if ((move & both) == 0 && move != 0) {
                        moves.push_back(move | state & ~piece);
                    }
                }
            }

            // Southeasterly capture
            move = slideSouth(slideEast(piece));
            // No friendly collision and a opp collision
            if ((move & ownState) == 0 && (move & oppState) != 0 && move != 0) {
                moves.push_back(move | state & ~piece);
            }

            // Southwesterly capture
            move = slideSouth(slideWest(piece));
            // No friendly collision and a opp collision
            if ((move & ownState) == 0 && (move & oppState) != 0 && move != 0) {
                moves.push_back(move | state & ~piece);
            }
        }
    }
    return moves;
}

std::vector<bitboard> horsePseudoLegalMoves(bitboard own, bitboard opp,
                                            bitboard state) {
    bitboard move;
    std::vector<bitboard> moves;

    std::vector<bitboard> pieces = getAllPieces(state);

    // Each move requires no collisions with friendly pieces
    for (auto& piece : pieces) {
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

// TODO include castling
std::vector<bitboard> castlePseudoLegalMoves(bitboard ownState,
                                             bitboard oppState,
                                             bitboard state) {
    bitboard move;
    std::vector<bitboard> moves;

    std::vector<bitboard> pieces = getAllPieces(state);

    for (auto& piece : pieces) {
        // Slide north
        move = piece;
        while (slideNorth(move) != 0) {
            move = slideNorth(move);
            // If hit friend: don't add this move and stop
            if ((move & ownState) != 0) {
                break;
            }
            // If hit enemy:  add this move and stop
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

std::vector<bitboard> bishopPseudoLegalMoves(bitboard ownState,
                                             bitboard oppState,
                                             bitboard state) {
    bitboard move;
    std::vector<bitboard> moves;

    std::vector<bitboard> pieces = getAllPieces(state);

    for (auto& piece : pieces) {
        // Slide north east
        move = piece;
        while (slideNorth(slideEast(move)) != 0) {
            move = slideNorth(slideEast(move));
            // If hit friend: don't add this move and stop
            if ((move & ownState) != 0) {
                break;
            }
            // If hit enemy:  add this move and stop
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

    // Queen moves equivalent to those of bishop and castle
    for (auto& piece : getAllPieces(state)) {
        std::vector<bitboard> diagonals =
            bishopPseudoLegalMoves(ownState, oppState, state);
        std::vector<bitboard> straights =
            castlePseudoLegalMoves(ownState, oppState, state);

        for (auto& move : diagonals) {
            moves.push_back(move | state & ~piece);
        }

        for (auto& move : straights) {
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

std::vector<bitboard> pseudoLegalFromIndex(int idx, team& white, team& black,
                                           bool colour) {
    team own = colour ? white : black;

    bitboard ownState = colour ? getTeamState(white) : getTeamState(black);
    bitboard oppState = colour ? getTeamState(black) : getTeamState(white);

    switch (idx) {
        case 0:
            return pawnPseudoLegalMoves(ownState, oppState, own.at(idx),
                                        colour);
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

std::vector<bitboard> legalMovesFromIndex(int idx, team& white, team& black,
                                          bool colour) {
    bitboard ownState = colour ? getTeamState(white) : getTeamState(black);
    bitboard oppState = colour ? getTeamState(black) : getTeamState(white);

    // Get the psuedo legals for this piece
    std::vector<bitboard> moves =
        pseudoLegalFromIndex(idx, white, black, colour);

    for (auto it = moves.begin(); it != moves.end();) {
        // Make the move
        auto [newWhite, newBlack] = makeMove(white, black, *it, idx, colour);
        team own = colour ? newWhite : newBlack;
        team opp = colour ? newBlack : newWhite;
        // Check if this piece's king is in check after move: remove it if it is
        if (isOwnKingInCheck(own, opp, colour))
            moves.erase(it);
        else
            ++it;
    }
    return moves;
}

std::vector<Move> getAllLegalMoves(team& white, team& black, bool colour) {
    std::vector<Move> moves{};
    // Iterate through each piece, adding its legal moves
    for (int piece = 0; piece < 6; piece++) {
        std::vector<bitboard> thisMoves =
            legalMovesFromIndex(piece, white, black, colour);
        for (bitboard move : thisMoves) {
            moves.push_back({move, piece});
        }
    }
    // TODO add castling here
    // TODO enpassant here
    return moves;
}

// Assumes input is legal
std::pair<bitboard, int> getRandomLegalMove(
    std::vector<std::pair<bitboard, int>> moves) {
    std::random_device rd;

    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    std::size_t randomMoveIndex = dist(rng);

    return moves.at(randomMoveIndex);
}

// XXX Not most efficient
bool isOwnKingInCheck(team& own, team& opp, bool colour) {
    bitboard ownState = getTeamState(own);
    bitboard oppState = getTeamState(opp);
    bitboard king = own.at(5);

    // Check queens
    for (bitboard queen : getAllPieces(opp.at(4))) {
        // If not on a diagonal or on the same rank OR file then not attacking
        // king
        if (!isDiagonal(king, queen)) {
            if (!(getRank(king) == getRank(queen) ||
                  getFile(king) == getFile(queen))) {
                continue;
            }
        }
        // If there is not a piece blocking the sight of a queen, then in check
        bitboard btwn = (getBetween(king, queen) & (ownState | oppState));
        if (btwn == 0) return true;
    }

    // Check castles
    for (bitboard& castle : getAllPieces(opp.at(2))) {
        // Castles require same rank or file to capture
        if (getRank(king) != getRank(castle) &&
            getFile(king) != getFile(castle))
            continue;
        // If there is not a piece blocking the sight of a castle, then in check
        if ((getBetween(king, castle) & (ownState | oppState)) == 0)
            return true;
    }

    // Check bishops
    for (bitboard& bishop : getAllPieces(opp.at(3))) {
        // Bishops require same diagonal or antidiagonal to capture
        // TODO compress this into logical operations on between and rank/file
        if (!isDiagonal(bishop, king)) continue;
        // If there is not a piece blocking the sight of a bishop, then in check
        if ((getBetween(king, bishop) & (ownState | oppState)) == 0)
            return true;
    }

    // Check horses
    std::array<int, 4> horseShifts = {17, 15, 6, 10};
    for (bitboard horse : getAllPieces(opp.at(1))) {
        std::vector<bitboard> moves =
            horsePseudoLegalMoves(oppState, ownState, horse);
        for (bitboard move : moves) {
            if ((king & move) != 0) return true;
        }
    }

    // Check pawns
    if (colour) {
        // Looking for black pawns that are north diagonal
        for (bitboard piece : getAllPieces(opp.at(0))) {
            if ((king & slideSouth(slideEast(piece))) != 0) return true;
            if ((king & slideSouth(slideWest(piece))) != 0) return true;
        }
    } else {
        // Looking for white pawns that are south diagonal
        for (bitboard piece : getAllPieces(opp.at(0))) {
            if ((king & slideNorth(slideEast(piece))) != 0) return true;
            if ((king & slideNorth(slideWest(piece))) != 0) return true;
        }
    }

    // Check King
    if ((king & slideNorth(opp.at(5))) != 0) return true;
    if ((king & slideNorth(slideEast(opp.at(5)))) != 0) return true;
    if ((king & slideEast(opp.at(5))) != 0) return true;
    if ((king & slideSouth(slideEast(opp.at(5)))) != 0) return true;
    if ((king & slideSouth(opp.at(5))) != 0) return true;
    if ((king & slideSouth(slideWest(opp.at(5)))) != 0) return true;
    if ((king & slideWest(opp.at(5))) != 0) return true;
    if ((king & slideNorth(slideWest(opp.at(5)))) != 0) return true;

    return false;
}
