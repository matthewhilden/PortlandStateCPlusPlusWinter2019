#include "piece.h"

// Get color of piece
// Returns integer value
int piece::get_type()
{
    return _pieceColor;
}

// Move the piece down one position
// Representative of moving down one y-coordinate,
// adds one to each y-component
void piece::move_down()
{
    _one.second = _one.second + 1;
    _two.second = _two.second + 1;
    _three.second = _three.second + 1;
    _four.second = _four.second + 1;
}

// Move the piece left one position
// Representative of moving down one x-coordinate,
// subtracts one from each x-component
void piece::move_left()
{
    _one.first = _one.first - 1;
    _two.first = _two.first - 1;
    _three.first = _three.first - 1;
    _four.first = _four.first - 1;
}

// Move the piece right one position
// Representative of moving up one x-coordinate,
// adds one to each x-component
void piece::move_right()
{
    _one.first = _one.first + 1;
    _two.first = _two.first + 1;
    _three.first = _three.first + 1;
    _four.first = _four.first + 1;
}

// Get first point of the piece
std::pair<int, int> & piece::get_one()
{
    return _one;
}

// Get second point of the piece
std::pair<int, int> & piece::get_two()
{
    return _two;
}

// Get third point of the piece
std::pair<int, int> & piece::get_three()
{
    return _three;
}

// Get fourth point of the piece
std::pair<int, int> & piece::get_four()
{
    return _four;
}
