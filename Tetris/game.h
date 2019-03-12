#pragma once

#include "board.h"
#include "piece.h"

#include <ctime>
#include <iostream>

class game
{
    private:

        // Create a list of pieces stored for counting statistics, etc.
        // Create a way to track current score and hiscores.
        // Output to a file the hiscores and read in/out on new game.

        bool _paused;
        bool _gameOver;

        int _level;
        int _linesCleared;
        int _score;
        int _hiscore;

        board _b;
        piece * _currentPiece;
        piece * _nextPiece;

    public:

        game();
        ~game();

        bool toggle_pause();
        bool paused();
        void reset_game();

        int get_level();
        int get_lines();
        int get_score();
        int get_hiscore();

        bool inside_bucket(std::pair<int, int> & point);                // Check if within left, right, down boundaries
        bool check_board_position_filled(std::pair<int, int> & point);  // Get board position value

        bool check_movement_valid(int direction);       // Check if movement or rotation is valid
        bool check_rotation_valid();

        bool move_piece(int direction);			// Apply movement to current piece
        bool rotate_piece();

        void remove_current_piece();			// Updating piece location in board
        void place_current_piece();

        void check_clear_rows();
        void lock_piece_and_replace();          // Switch to next piece in queue

        bool game_over();

        piece * generate_piece();
        piece * generate_piece(piece * previous);
        piece * get_next_piece();

        int get_board_position(int row, int col);
};
