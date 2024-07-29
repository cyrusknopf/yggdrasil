#ifndef _UTILSH_
#define _UTILSH_

#include <array>
#include <cstdint>
#include <regex>
#include <vector>

// For clarity
using bitboard = uint64_t;
using team = std::array<bitboard, 6>;

// RegEx for recognising a valid input
const std::regex squareRe{"[a-h][1-8]"};

/*
 * Returns the file (column) of a piece
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return integer corresponding to the file of the piece
 */
int getRank(bitboard state);

/*
 * Returns the rank (row) of a piece
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return integer corresponding to the rank of the piece
 */
int getFile(bitboard state);

bitboard getBetween(bitboard sq1, bitboard sq2);

/*
 * Given a chess coordinate (e.g. a3) in string form, returns a bitboard with a
 * single piece at that coordinate
 *
 * @param [coord] coordinate in string form
 * @return bitboard with a 1 at the coordinate only
 */
bitboard coordinateToState(const std::string& coord);

/*
 * Moves the provided piece north one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved up one square
 */
constexpr bitboard slideNorth(bitboard state) { return state <<= 8; }
/*
 * Moves the provided piece south one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved down one square
 */
constexpr bitboard slideSouth(bitboard state) { return state >>= 8; }

/*
 * Moves the provided piece east one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved right one square
 */
constexpr bitboard slideEast(bitboard state) {
    return (state >>= 1) & 0x7F7F7F7F7F7F7F7FULL;
}

/*
 * Moves the provided piece west one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved left one square
 */
constexpr bitboard slideWest(uint64_t state) {
    return (state <<= 1) & 0xFEFEFEFEFEFEFEFE;
}
/*
 * Returns an array of bitboards, each with a single piece, from a bitboard with
 * multiple pieces
 *
 * @param [state] bitboard with multiple pieces, which each piece will be
 * extracted from
 * @return vector of bitboards, each with a single piece from the original board
 * on it
 */
std::vector<bitboard> getAllPieces(bitboard state);

/*
 * Searches for a piece in an array which contains a 1 at the location specified
 * in the bitboard of square
 *
 * @param [square] bitboard containing a single piece which is to be searched
 * for
 * @param [target] array of bitboards which are to be searched
 * @return pair containing <bitboard which contains the square, index of the
 * bitboard in the searched array>
 */
std::pair<bitboard, int> findPiece(bitboard square,
                                   std::array<bitboard, 6>& target);

/*
 * Capture logic for a board containing possibly many pieces (victim), and a
 * single piece (captor) which will capture one of those pieces. Returns victim
 * after capture
 *
 * @param [victim] bitboard to be captured
 * @param [captor] bitboard with a single piece, will capture one of victim's
 * pieces
 * @return victim after capture
 */
bitboard performCapture(bitboard victim, bitboard captor);

/*
 * Given the two team arrays, creates the string representation of the board
 *
 * @param [whitePieces] white pieces bitboard array
 * @param [blackPieces] black pieces bitboard array
 * @return string representation of the game
 */
std::string gameStateToString(team whitePieces, team blackPieces);

// Clears the terminal window, intended to preceed printing of the board
void clearTerm();
#endif  // !_UTILSH_
