#pragma once

#include "piece.h"

#include <iostream>
#include <vector>

const int BOARD_WIDTH = 10;     // Number of columns in board (default 10)
const int BOARD_HEIGHT = 20;    // Number of rows in board (default 20)

const int EMPTY_SPACE = -1;     // Constant for empty board position value
const int LEFT = 1;             // Constants for directional movement of peices
const int RIGHT = 2;
const int DOWN = 3;

class piece;

class board
{

    private:

        /*
         *  A Tetris board is represented as a 2D vector of integer values, containing a specified number
         *  of rows and columns. The integer values correspond to a specific piece, used by the GUI for
         *  coloring purposes. The board class has control for manipulating the values of the board at
         *  specified x-y coordinates. Our coordinate system asserts that the positive-x direction is increasing
         *  to the right, and the positive-y direction is increasing downward.
         */

        std::vector<std::vector<int>> _board;       // 2D vector storage for board contents

    public:

        board();

        bool place_piece_at_start(piece * p);                           // Place piece at it's correct starting position
        bool check_position_filled(std::pair<int, int> & point);        // Check if board position is filled
        bool check_row_filled(int row);                                 // Check if entire row (specified) is filled

        int get_board_position(int row, int col);       // Get value at specified row and column (x-y coord)

        void fill_position(std::pair<int, int> & point, int value);     // Fill board position with specified value
        void unfill_position(std::pair<int, int> & point);              // Unfill board position (fill to default)
        void shift_down(int row);                                       // Shift board contents down one row (to specified row)
        void clear_board();                                             // Clear all board contents (set to default value)
};
