#include <array>
#include <cstdint>

/*
 * Contains the main logic of the game of chess.
 */
class Chess {
public:
  /*
   * The 6 bitboards each representing a white piece.
   * Index  |   Piece
   * 0          White Pawn
   * 1          White Horse
   * 2          White Castle
   * 3          White Bishop
   * 4          White Queen
   * 5          White King
   */

  std::array<uint64_t, 6> whiteBitboards;
  /*
   * The 6 bitboards each representing a black piece.
   * Index  |   Piece
   * 0          Black Pawn
   * 1          Black Horse
   * 2          Black Castle
   * 3          Black Bishop
   * 4          Black Queen
   * 5          Black King
   */
  std::array<uint64_t, 6> blackBitboards;

  /*
   * Populates the `whiteBitboards` and `blackBitboards` arrays with the
   * starting position of each piece
   */
  void initGame();

  uint64_t getGameState();
  uint64_t getGameState(bool colour);
};
