#pragma once

#include "board.h"

#include <cstdlib>
#include <iostream>

const int MAX_PIECES = 7;

class piece
{
    protected:

        /*  A Tetris piece is modelled as a combination of four pairs of integers,
         *  where each pair represents a x-y coordinate that corresponds to a x-y
         *  position on, or off, the Tetris game board, and an integer value that
         *  represents the rotation of the piece. A piece has four distinct
         *  rotations, with a rotation representing a 90 degree clockwise transformation.
         *  A Tetris piece can move left, right or down.
         */

        int _rotation;
        int _pieceColor;

        std::pair<int, int> _one;
        std::pair<int, int> _two;
        std::pair<int, int> _three;
        std::pair<int, int> _four;

    public:

        virtual void rotate() = 0;              // Interface for piece rotation
        virtual void rotate_reverse() = 0;      // Interface for reversal rotation
        virtual ~piece() {}                     // Destructor

        void move_down();                       // Control for moving pieces in speicifed directions
        void move_left();
        void move_right();

        int get_type();                         // Get piece type (int value)

        std::pair<int, int> & get_one();        // Control for getting individual x-y coordinates of piece
        std::pair<int, int> & get_two();
        std::pair<int, int> & get_three();
        std::pair<int, int> & get_four();
};
