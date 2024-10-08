#ifndef _INITS_H_
#define _INITS_H_

#include "utils.h"

// White piece init positions
constexpr bitboard whitePawnInit = 0xFF00;
constexpr bitboard whiteHorseInit = 0x42;
constexpr bitboard whiteCastleInit = 0x81;
constexpr bitboard whiteBishopInit = 0x24;
constexpr bitboard whiteQueenInit = 0x10;
constexpr bitboard whiteKingInit = 0x8;
constexpr team whiteInit = {whitePawnInit,   whiteHorseInit, whiteCastleInit,
                            whiteBishopInit, whiteQueenInit, whiteKingInit};

// Black piece init positions
constexpr bitboard blackPawnInit = 0x00FF000000000000;
constexpr bitboard blackHorseInit = 0x4200000000000000;
constexpr bitboard blackCastleInit = 0x8100000000000000;
constexpr bitboard blackBishopInit = 0x2400000000000000;
constexpr bitboard blackQueenInit = 0x1000000000000000;
constexpr bitboard blackKingInit = 0x800000000000000;
constexpr team blackInit = {blackPawnInit,   blackHorseInit, blackCastleInit,
                            blackBishopInit, blackQueenInit, blackKingInit};

// Symbols of pieces for terminal output
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

#endif  // !_INITS_H_
