#pragma once

#include "board.h"
#include "piece.h"

#include <ctime>
#include <iostream>

class game
{
    private:

        /*
         *  A Tetris game consists of a board and two pieces, a current piece (in play), and
         *  a secondary piece that represents the next piece for play. A game repeatedly shifts
         *  the current piece down in the game board, while allowing the user to manipulate the position
         *  of the piece through 90-degree rotations and left/right/downward (cartesian) shifts.
         *  Once the piece can no longer shift vertically (or the player downshifts the piece), the piece
         *  is locked into position, and the secodnary piece is place on it's specified starting position,
         *  and into play. The game continues until placing a new piece causes a collision, or a piece locks
         *  in a position where any of its contents are outside of the board boundaries. The game maintains
         *  control of user score, number of lines cleared, hiscore, and state for pausing and game over.
         */

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

        game();         // Default constructor
        ~game();        // Default destructor

        int get_level();                            // Return current level
        int get_lines();                            // Return number of cleared lines
        int get_score();                            // Return current score
        int get_hiscore();                          // Return current hiscore
        int get_board_position(int row, int col);   // Return value at specifed board position (x-y coordinate)

        bool inside_bucket(std::pair<int, int> & point);        // Check if within left, right, down boundaries
        bool check_movement_valid(int direction);               // Check if specified movement is valid
        bool check_rotation_valid();                            // Check if current piece can rotate
        bool move_piece(int direction);                         // Apply movement to current piece
        bool rotate_piece();                                    // Rotate current piece 90-degrees clockwise
        bool check_clear_rows();                                // Check and clear full rows on piece locking
        bool lock_piece_and_replace();                          // Lock current piece and switch to new piece, generating new secondary piece
        bool paused();                                          // Check if game is paused
        bool game_over();                                       // Check if game is over

        void remove_current_piece();                    // Remove current piece from board
        void place_current_piece();                     // Place current piece on board
        void toggle_pause();                            // Toggle pause game state
        void update_score_level(int linesCleared);      // Update the score and level
        void reset_game();                              // Reset game to starting state

        piece * generate_piece();                       // Generate a new piece
        piece * generate_piece(piece * previous);       // Generate a secondary piece (using previous data)
        piece * get_next_piece();                       // Get secondary piece

};
