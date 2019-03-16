#include "l.h"

// Default constructor
// Intializes the four points comprising an L piece
// Sets rotation to 0 and piece type to L
l::l()
{
    _one.first = BOARD_WIDTH / 2 - 2;
    _one.second = 0;

    _two.first = BOARD_WIDTH / 2 - 2;
    _two.second = 1;

    _three.first = BOARD_WIDTH / 2 - 1;
    _three.second = 0;

    _four.first = BOARD_WIDTH / 2;
    _four.second = 0;

    _rotation = 0;
    _pieceColor = 2;
}

// Default destructor
l::~l()
{
}

// Rotates the piece 90 degrees clockwise around the pivot point
void l::rotate()
{
    if (_rotation == 0)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second - 1;

        _two.second = _two.second - 2;

        _four.first = _four.first - 1;
        _four.second = _four.second + 1;

        _rotation = 1;
    }
    else if (_rotation == 1)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second + 1;

        _two.first = _two.first + 2;

        _four.first = _four.first - 1;
        _four.second = _four.second - 1;

        _rotation = 2;
    }
    else if (_rotation == 2)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second + 1;

        _two.second = _two.second + 2;

        _four.first = _four.first + 1;
        _four.second = _four.second - 1;

        _rotation = 3;
    }
    else if (_rotation == 3)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second - 1;

        _two.first = _two.first - 2;

        _four.first = _four.first + 1;
        _four.second = _four.second + 1;

        _rotation = 0;
    }
}

// Rotate the piece 90 degrees counterclockwise around the pivot point
void l::rotate_reverse()
{
    if (_rotation == 0)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second + 1;

        _two.first = _two.first + 2;

        _four.first = _four.first - 1;
        _four.second = _four.second - 1;

        _rotation = 3;
    }
    else if (_rotation == 3)
    {
        _one.first = _one.first + 1;
        _one.second = _one.second - 1;

        _two.second = _two.second - 2;

        _four.first = _four.first - 1;
        _four.second = _four.second + 1;

        _rotation = 2;
    }
    else if (_rotation == 2)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second - 1;

        _two.first = _two.first - 2;

        _four.first = _four.first + 1;
        _four.second = _four.second + 1;

        _rotation = 1;
    }
    else if (_rotation == 1)
    {
        _one.first = _one.first - 1;
        _one.second = _one.second + 1;

        _two.second = _two.second + 2;

        _four.first = _four.first + 1;
        _four.second = _four.second - 1;

        _rotation = 0;
    }
}
