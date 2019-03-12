#include "o.h"

// Default constructor
// Initialzes the four points comprising an O piece
// Sets rotation to 0 and piece type to O
o::o()
{
    _one.first = BOARD_WIDTH / 2 - 1;
    _one.second = 0;

    _two.first = BOARD_WIDTH / 2;
    _two.second = 0;

    _three.first = BOARD_WIDTH / 2 - 1;
    _three.second = 1;

    _four.first = BOARD_WIDTH / 2;
    _four.second = 1;

    _rotation = 0;
    _pieceColor = 3;
}

// Default destructor
o::~o()
{
}

// Rotates the piece 90 degrees clockwise around the pivot point
// For a square piece, the rotation does nothing
void o::rotate()
{
    // Do nothing
}
