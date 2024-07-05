#ifndef _INITSH_
#define _INITSH_

#include "utils.h"

constexpr bitboard whitePawnInit = 0xFF00;
constexpr bitboard whiteHorseInit = 0x42;
constexpr bitboard whiteCastleInit = 0x81;
constexpr bitboard whiteBishopInit = 0x24;
constexpr bitboard whiteQueenInit = 0x10;
constexpr bitboard whiteKingInit = 0x8;

const std::string WPAWN = "♙";
const std::string WCASTLE = "♖";
const std::string WHORSE = "♘";
const std::string WBISHOP = "♗";
const std::string WQUEEN = "♕";
const std::string WKING = "♔";

const std::string BPAWN = "♟";
const std::string BCASTLE = "♜";
const std::string BHORSE = "♞";
const std::string BBISHOP = "♝";
const std::string BQUEEN = "♛";
const std::string BKING = "♚";

#endif // !_INITSH_
