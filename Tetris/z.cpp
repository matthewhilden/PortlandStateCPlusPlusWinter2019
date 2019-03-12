#include "z.h"

// Default constructor
// Initializes the four points comprising a Z piece
// Sets rotation to 0 and piece type to Z
z::z()
{
    _one.first = BOARD_WIDTH / 2 - 2;
    _one.second = 0;

    _two.first = BOARD_WIDTH / 2 - 1;
    _two.second = 0;

    _three.first = BOARD_WIDTH / 2 - 1;
    _three.second = 1;

    _four.first = BOARD_WIDTH / 2;
    _four.second = 1;

    _rotation = 0;
    _pieceColor = 6;
}

// Default destructor
z::~z()
{
}

// Rotate the piece 90 degrees clockwise around the pivot point
void z::rotate()
{
    if (_rotation == 0)
    {
        _one.first = _one.first + 2;

        _two.first = _two.first + 1;
        _two.second = _two.second + 1;

        _four.first = _four.first - 1;
        _four.second = _four.second + 1;

        _rotation = 1;
    }
    else if (_rotation == 1)
    {
        _one.second = _one.second + 2;

        _two.first = _two.first - 1;
        _two.second = _two.second + 1;

        _four.first = _four.first - 1;
        _four.second = _four.second - 1;

        _rotation = 2;
    }
    else if (_rotation == 2)
    {
        _one.first = _one.first - 2;

        _two.first = _two.first - 1;
        _two.second = _two.second - 1;

        _four.first = _four.first + 1;
        _four.second = _four.second - 1;

        _rotation = 3;
    }
    else if (_rotation == 3)
    {
        _one.second = _one.second - 2;

        _two.first = _two.first + 1;
        _two.second = _two.second - 1;

        _four.first = _four.first + 1;
        _four.second = _four.second + 1;

        _rotation = 0;
    }
}
