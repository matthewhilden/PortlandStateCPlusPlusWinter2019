#include "board.h"
#include "piece.h"

#include "i.h"
#include "j.h"
#include "l.h"
#include "o.h"
#include "s.h"
#include "t.h"
#include "z.h"

// Default constructor
// Sets the size of the vector holding the board contents
board::board()
{
    _board.resize(BOARD_WIDTH);

    for (int y = 0; y < BOARD_WIDTH; y++)
    {
        _board[y].resize(BOARD_HEIGHT);

        for (int x = 0; x < BOARD_HEIGHT; x++)
        {
            _board[y][x] = -1;
        }
    }
}

// Clear entire board contents
// Reset the entire board to default values
void board::clear_board()
{
    for (int y = 0; y < BOARD_WIDTH; y++)
    {
        for (int x = 0; x < BOARD_HEIGHT; x++)
        {
            _board[y][x] = -1;
        }
    }
}

// Get board position at specified x-y coordinate
int board::get_board_position(int row, int col)
{
    return _board[row][col];
}

// Places the input piece at its starting position on the board
// Returns true if the placement is valid, false if collision
bool board::place_piece_at_start(piece * p)
{
    std::pair<int, int> pointOne = p->get_one();
    std::pair<int, int> pointTwo = p->get_two();
    std::pair<int, int> pointThree = p->get_three();
    std::pair<int, int> pointFour = p->get_four();

    bool flag = false;

    if (!check_position_filled(pointOne) && !check_position_filled(pointTwo)
                         && !check_position_filled(pointThree)
                         && !check_position_filled(pointFour))
    {
        flag = true;	// No collision
    }

    int value = p->get_type();

    fill_position(pointOne, value);
    fill_position(pointTwo, value);
    fill_position(pointThree, value);
    fill_position(pointFour, value);

    return flag;
}

// Updates the position of the board as filled
// The input pair (point) corresponds to an x-y coordinate on the board
// Will not update pieces that are oustide board range
void board::fill_position(std::pair<int, int> & point, int value)
{
    int first = point.first;
    int second = point.second;

    if (first >= 0 && first < BOARD_WIDTH)
    {
        if (second >= 0 && second < BOARD_HEIGHT)
        {
            _board[first][second] = value;
        }
    }
}

// Updates the position of the board as empty
// The input pair (point) corresponds to an x-y coordinate on the board
// Will not update pieces that are oustide board range
void board::unfill_position(std::pair<int, int> & point)
{
    int first = point.first;
    int second = point.second;

    if (first >= 0 && first < BOARD_WIDTH)
    {
        if (second >= 0 && second < BOARD_HEIGHT)
        {
            _board[first][second] = -1;
        }
    }
}

// Check if specified point (x-y coordinate) is filled
// Returns true if filled, false otherwise
// Returns false if the point is not within the four board walls.
bool board::check_position_filled(std::pair<int, int> & point)
{
    int first = point.first;
    int second = point.second;

    if ((first < 0 || first >= BOARD_WIDTH) || (second < 0 || second >= BOARD_HEIGHT))
    {
        // Throw Error Here ...

        return false;
    }
    else
    {
        if (_board[first][second] != -1)
        {
            return true;
        }
    }

    return false;
}

// Check if the entire row at the input position is filled
// This is used for row shifting full rows when placing pieces
// Return true if the specified row is completely filled, false otherwise
bool board::check_row_filled(int row)
{
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        if (_board[x][row] == -1)
        {
            return false;
        }
    }
    return true;
}

// Shifts the board down one space to the current row
// Fills the row at the top of the board as empty
void board::shift_down(int row)
{
    for (int y = row; y > 0; y--)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            _board[x][y] = _board[x][y - 1];
        }
    }

    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        _board[x][0] = -1;
    }
}
