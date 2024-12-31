#ifndef _USER_AGENT_
#define _USER_AGENT_

#include <optional>
#include <string>

#include "utils.h"

struct MoveInput {
    bitboard newBoard;
    int fromIdx;
    bitboard toSquare;
};

class UserAgent {
   private:
    /*
     * Takes input from user via cin, expecting a coordinate on a chess board.
     * If the input is not a valid coordinate, returns a nullopt, otherwise,
     * returns a bitboard with a single 1 at the provided coordinate
     *
     * @return either bitboard of inputted coordinate or nullopt
     */
    std::optional<bitboard> readSquare();
    /*
     * Loops until two valid chess square coordinates have been entered via
     * `readSquare`. Prints the chess board state to stdout. Contains a message
     * which can give user feedback such as invalid move, etc
     *
     * @param [white] white team array of bitboards
     * @param [black] black team array of bitboards
     * @param [message] message to display under chess board in stdout
     * @returns pair containing single 1 bitboards of the to and from squares
     */
    std::pair<bitboard, bitboard> takeToAndFrom(team& white, team& black,
                                                std::string& message);
    /*
     * Loops until a valid move has been taken from `takeToAndFrom`.
     * Checks that there is a piece at the 'from square' and that the 'to
     * square' is a valid move for that piece. Retruns a struct of information
     * about the move.
     *
     * @param [white] white team array of bitboards
     * @param [black] black team array of bitboards
     * @param [turn] turn of player (white = true)
     * @param [message] message to display under chess board in stdout
     * @returns <piece board after move, index of piece,
     * singleton bitboard of 'to square'>
     */
    MoveInput takeMove(team& whiteBitboards, team& blackBitboards, bool turn,
                       std::string& message);

   public:
    UserAgent(){};
    std::pair<team, team> takeTurn(team whiteBitboards, team blackBitboards,
                                   bool turn, std::string& message);
};
#endif  // !_USER_AGENT_
