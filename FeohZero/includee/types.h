#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t U8;

// enum for piece types
typedef enum { PAWN = 0, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE } PieceType;

// enum for castling rights (2 bits for each player)
typedef enum {
    CANNOT_CASTLE = 0,   // 00
    CAN_CASTLE_OO = 1,   // 01
    CAN_CASTLE_OOO = 2,  // 10
    CAN_CASTLE = 3       // 11 (both sides)
} CastleRights;

// enum for move type (1 bit in total)
typedef enum { WHITE = 0, BLACK = 1 } Turn;

// enum for move flags
typedef enum {
    NORMAL_MOVE = 0,       // 00000
    CAPTURE_MOVE = 1,      // 00001
    EN_PASSANT = 2,        // 00010
    CASTLING = 4,          // 00100
    PROMOTION = 8,         // 01000
    DOUBLE_PAWN_PUSH = 16  // 10000
} MoveFlags;

// define structure for representing the board state
typedef struct {
    // use 2 arrays of 6 for black(1) and white(0)
    U64 pieces[2][6];

    // 0 for white, 1 for black, 2 for both
    U64 occupied[3];

    Turn turn : 1;                  // 1 bit
    CastleRights castle_white : 2;  // 2 bits
    CastleRights castle_black : 2;  // 2 bits

    U8 ep_square;   // store en_passant square
    U8 half_move;   // half move counter
    U64 key;        // Zobrist key
    U16 full_move;  // Full move counter
} Board;

typedef struct {
    // do move
    U8 from;   // start square (0-63)
    U8 to;     // final square (0-63)
    U8 promo;  // promotion piece type

    // undo move
    U8 piece;     // moved piece type
    U8 captured;  // captured piece type
    U8 flags;     // special move flags
    U8 ep;        // en passant square (0-63)
    U8 castle_white;    // store old castling rights
    U8 castle_black;
    int score;    // Heuristic score of a move

} Move;

typedef struct {
    Move moves[256];  // array of moves
    int count;        // number of moves stored
} MoveList;

// struct for LUTs
typedef struct {
    U64 knight[64];
    U64 king[64];
    U64 pawn[2][64];
    U64 rook[102400];
    U64 bishop[5248];
} LUT;

#endif
