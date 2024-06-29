#include <array>
#include <cstdint>

/*
 * Contains the main logic of the game of chess.
 */
class Chess {
public:
  /*
   * The 12 bitboards, each representing a piece of either black or white.
   * Index  |   Piece
   * 0          White Pawn
   * 1          White Horse
   * 2          White Castle
   * 3          White Bishop
   * 4          White Queen
   * 5          White King
   * 6          Black Pawn
   * 7          Black Horse
   * 8          Black Castle
   * 9          Black Bishop
   * 10         Black Queen
   * 11         Black King
   */
  std::array<uint64_t, 12> bitboards;

  /*
   * Populates the `biboards` array with the starting position of each piece
   */
  void initGame();
};
