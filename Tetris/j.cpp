#include "j.h"

// Default constructor
// Initializes the four points comprising a J piece
// Sets rotation to 0 and piece type to J
j::j()
{
    _one.first = BOARD_WIDTH / 2 - 2;
    _one.second = 0;

    _two.first = BOARD_WIDTH / 2 - 1;	// Pivot
    _two.second = 0;

    _three.first = BOARD_WIDTH / 2;
    _three.second = 0;

    _four.first = BOARD_WIDTH / 2;
    _four.second = 1;

    _rotation = 0;
    _pieceColor = 1;
}

// Default destructor
j::~j()
{
}

// Rotate the piece 90 degrees clockwise around the pivot point
void j::rotate()
{
    if (_rotation == 0)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second - 1;

        _three.first = _three.first - 1;
        _three.second = _three.second + 1;

        _four.first = _four.first - 2;

        _rotation = 1;
    }
    else if (_rotation == 1)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second + 1;

        _three.first = _three.first - 1;
        _three.second = _three.second - 1;

        _four.second = _four.second - 2;

        _rotation = 2;
    }
    else if (_rotation == 2)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second + 1;

        _three.first = _three.first + 1;
        _three.second = _three.second - 1;

        _four.first = _four.first + 2;

        _rotation = 3;
    }
    else if (_rotation == 3)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second - 1;

        _three.first = _three.first + 1;
        _three.second = _three.second + 1;

        _four.second = _four.second + 2;

        _rotation = 0;
    }
}

// Rotate the piece 90 degrees counterclockwise around the pivot point
void j::rotate_reverse()
{
    if (_rotation == 0)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second + 1;

        _three.first = _three.first - 1;
        _three.second = _three.second - 1;

        _four.second = _four.second - 2;

        _rotation = 3;
    }
    else if (_rotation == 3)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second - 1;

        _three.first = _three.first - 1;
        _three.second = _three.second + 1;

        _four.first = _four.first - 2;

        _rotation = 2;
    }
    else if (_rotation == 2)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second - 1;

        _three.first = _three.first + 1;
        _three.second = _three.second + 1;

        _four.second = _four.second + 2;

        _rotation = 1;
    }
    else if (_rotation == 1)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second + 1;

        _three.first = _three.first + 1;
        _three.second = _three.second - 1;

        _four.first = _four.first + 2;

        _rotation = 0;
    }
}
