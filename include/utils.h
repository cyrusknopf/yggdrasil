#ifndef _UTILSH_
#define _UTILSH_

#include <array>
#include <cstdint>
#include <random>
#include <regex>
#include <vector>

// For clarity
using bitboard = uint64_t;
using team = std::array<bitboard, 6>;

// RegEx for recognising a valid input
const std::regex squareRe{"[a-h][1-8]"};

/*
 * Returns the rank (row) of a piece
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return integer corresponding to the rank of the piece
 */
int getRank(bitboard state);

/*
 * Returns the file (column) of a piece
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return integer corresponding to the file of the piece
 */
int getFile(bitboard state);

/*
 * Given two singleton bitboards, gets the bitboard containing 1s in either a
 * diagonal, horizontal or vertical line between the two pieces, piece exclusive
 * If the two pieces are not on the same diagonal or rank or file, returns 0
 *
 * @param [board1] singleton bitboard
 * @param [board2] singleton bitboard
 * @returns bitboard containing ones in the line between two pieces
 */
bitboard getBetween(bitboard board1, bitboard board2);

/*
 * Given two singleton bitboards, returns true if the pieces are on the same
 * diagonal, false otherwise
 *
 * @param [sq1] singleton bitboard
 * @param [sq2] singleton bitboard
 * @returns true if on diagonal, false otherwise
 */
bool isDiagonal(bitboard sq1, bitboard sq2);

/*
 * Given a chess coordinate (e.g. a3) in string form, returns a bitboard with a
 * single piece at that coordinate
 *
 * @param [coord] coordinate in string form
 * @return bitboard with a 1 at the coordinate only
 */
bitboard coordinateToState(const std::string& coord);

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
 * Given a single bitboard (possibly with multiple pieces), adds the
 * provided symbol to each location on the provided string board
 * representation
 *
 * @param [board] string representation of the board
 * @param [pieceBitboard] bitboard to add to the string representation
 * @param [symbol] symbol to use as representation at each location
 * @return updated string representation of the board
 */
std::string addPieceToStringBoard(std::string& board, bitboard pieceBitboard,
                                  const std::string& symbol);

/*
 * Given the two team arrays, creates the string representation of the board
 *
 * @param [whitePieces] white pieces bitboard array
 * @param [blackPieces] black pieces bitboard array
 * @return string representation of the game
 */
std::string gameStateToString(team whitePieces, team blackPieces);

/*
 * Get a random element from a vector of that type of element
 *
 * @param [container] vector of elements
 * @param [seed] seed for MT19937
 * @returns random element of `container`
 */
template <typename T>
T getRandom(std::vector<T> container, int seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::size_t> dist(0, container.size() - 1);
    std::size_t index = dist(rng);
    return container.at(index);
}

// Clears the terminal window, intended to preceed printing of the board
void clearTerm();

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

#endif  // !_UTILSH_
