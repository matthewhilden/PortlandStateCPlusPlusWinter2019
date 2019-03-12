#pragma once

#include "piece.h"

#include <iostream>
#include <vector>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

const int LEFT = 1;
const int RIGHT = 2;
const int DOWN = 3;

class piece;

class board
{

    private:

        std::vector<std::vector<int>> _board;

    public:

        board();

        bool check_position_filled(std::pair<int, int> & point);
        void fill_position(std::pair<int, int> & point, int value);
        void unfill_position(std::pair<int, int> & point);
        bool place_piece_at_start(piece * p);

        bool check_row_filled(int row);
        void shift_down(int row);

        void clear_board();

        int get_board_position(int row, int col);
};
