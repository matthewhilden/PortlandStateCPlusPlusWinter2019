#include "game.h"
#include "board.h"

#include "i.h"
#include "j.h"
#include "l.h"
#include "o.h"
#include "s.h"
#include "t.h"
#include "z.h"

#include <set>
#include <iterator>

// Default constructor
// Generates a random game piece for current and next, places the piece at the start
game::game() : _paused(false), _gameOver(true), _level(0), _linesCleared(0), _score(0), _hiscore(10000)
{
    _currentPiece = generate_piece();
    _nextPiece = generate_piece();
}

// Destructor
// Frees dynamic memory used in pointers
game::~game()
{
    _currentPiece = nullptr;
    _nextPiece = nullptr;
    delete _currentPiece;
    delete _nextPiece;
}

// Get current game level
int game::get_level()
{
    return _level;
}

// Get current lines cleared
int game::get_lines()
{
    return _linesCleared;
}

// Get current score
int game::get_score()
{
    return _score;
}

// Get hiscore
int game::get_hiscore()
{
    return _hiscore;
}

// Check if the game is over
// Return the gameOver flag
bool game::game_over()
{
    return _gameOver;
}

// Reset game state
// Clear board, generate new pieces
void game::reset_game()
{
    _b.clear_board();

    _currentPiece = generate_piece();
    _nextPiece = generate_piece(_currentPiece);

    _b.place_piece_at_start(_currentPiece);

    _gameOver = false;
    _paused = false;

    if (_score > _hiscore)      // Update hiscore
    {
        _hiscore = _score;
    }

    _level = 0;                 // Reset counters
    _linesCleared = 0;
    _score = 0;
}

// Toggle pause flag
// Flips the boolean value of the paused field
// Returns the new boolean value
void game::toggle_pause()
{
    _paused = !_paused;
}

// Check if game is paused
// Returns boolean value
bool game::paused()
{
    return _paused;
}

// Get board value at specified x-y coordinate
// Returns integer value at board position
int game::get_board_position(int row, int col)
{
    return _b.get_board_position(row, col);
}

// Check if current piece cleared and rows
// Checks if the current piece resulted in filled rows,
// resulting in row clears and shifting board down.
// Updates score and level based on Original Nintendo scoring system.
// Return false if locking piece above board boundary, true otherwise.
bool game::check_clear_rows()
{
    int cleared = 0;

    std::set<int> rows;

    rows.insert(_currentPiece->get_one().second);
    rows.insert(_currentPiece->get_two().second);
    rows.insert(_currentPiece->get_three().second);
    rows.insert(_currentPiece->get_four().second);

    std::set<int>::iterator iter = rows.begin();

    if (*iter < 0)
    {
        return false;
    }

    for (; iter != rows.end(); ++iter)
    {
        int current = *iter;
        if (_b.check_row_filled(current))
        {
            _b.shift_down(current);
            cleared++;
        }
    }

    update_score_level(cleared);

    return true;
}

// Update the game score and level based on input
void game::update_score_level(int linesCleared)
{
    if (linesCleared != 0)
    {
        if (linesCleared == 1)
        {
            _score += (40 * (_level + 1));
        }
        else if (linesCleared == 2)
        {
            _score += (100 * (_level + 1));
        }
        else if (linesCleared == 3)
        {
            _score += (300 * (_level + 1));
        }
        else if (linesCleared == 4)
        {
            _score += (1200 * (_level + 1));
        }

        _linesCleared += linesCleared;
        _level = _linesCleared / 10;
    }
}

// Locks the current piece and then swaps to the next piece in the queue,
// also generates a new next piece
// Returns false if endgame condition is met, true otherwise (game continues)
bool game::lock_piece_and_replace()
{
    if (!check_clear_rows())
    {
        _gameOver = true;   // End game condition
        return false;
    }

    _currentPiece = _nextPiece;
    _nextPiece = generate_piece(_currentPiece);

    if(!_b.place_piece_at_start(_currentPiece))
    {
        _gameOver = true;   // End game condition
        return false;
    }

    return true;
}

// Check if the current piece can move (validly) in the specified direction.
// A game of Tetris does not allow up movements, only Left, Right, and Down.
// Returns true if valid, false otherwise
bool game::check_movement_valid(int direction)
{
    std::pair<int, int> pointOne = _currentPiece->get_one();		// Get the components to check against the new point
    std::pair<int, int> pointTwo = _currentPiece->get_two();
    std::pair<int, int> pointThree = _currentPiece->get_three();
    std::pair<int, int> pointFour = _currentPiece->get_four();

    std::pair<int, int> updatedPointOne = pointOne;				// Make a copy of the components to apply the movement
    std::pair<int, int> updatedPointTwo = pointTwo;
    std::pair<int, int> updatedPointThree = pointThree;
    std::pair<int, int> updatedPointFour = pointFour;

    if (direction == LEFT)
    {
        updatedPointOne.first = updatedPointOne.first - 1;      // Update components
        updatedPointTwo.first = updatedPointTwo.first - 1;
        updatedPointThree.first = updatedPointThree.first - 1;
        updatedPointFour.first = updatedPointFour.first - 1;

    }
    else if (direction == RIGHT)
    {
        updatedPointOne.first = updatedPointOne.first + 1;
        updatedPointTwo.first = updatedPointTwo.first + 1;
        updatedPointThree.first = updatedPointThree.first + 1;
        updatedPointFour.first = updatedPointFour.first + 1;
    }
    else if (direction == DOWN)
    {
        updatedPointOne.second = updatedPointOne.second + 1;
        updatedPointTwo.second = updatedPointTwo.second + 1;
        updatedPointThree.second = updatedPointThree.second + 1;
        updatedPointFour.second = updatedPointFour.second + 1;
    }
    else	// ERROR
    {
        return false;
    }

    if (inside_bucket(updatedPointOne) && inside_bucket(updatedPointTwo)
                                       && inside_bucket(updatedPointThree)
                                       && inside_bucket(updatedPointFour))
    {
        if (_b.check_position_filled(updatedPointOne))
        {
            if (!(updatedPointOne == pointTwo || updatedPointOne == pointThree || updatedPointOne == pointFour))
            {
                return false;
            }
        }

        if (_b.check_position_filled(updatedPointTwo))
        {
            if (!(updatedPointTwo == pointOne || updatedPointTwo == pointThree || updatedPointTwo == pointFour))
            {
                return false;
            }
        }

        if (_b.check_position_filled(updatedPointThree))
        {
            if (!(updatedPointThree == pointOne || updatedPointThree == pointTwo || updatedPointThree == pointFour))
            {
                return false;
            }
        }

        if (_b.check_position_filled(updatedPointFour))
        {
            if (!(updatedPointFour == pointOne || updatedPointFour == pointTwo || updatedPointFour == pointThree))
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

// Check if the current piece is able to rotate from its current position.
// A rotation equates to a 90 degree clockwise transformation. Each piece has a pivot
// point that specified the axis of rotation around x-y coordinates. If a piece will
// move outside the boundaries of the board (left or right, not up), the rotation
// will fail. Later versions of Tetris have "wall kick" to combat this.
// Returns true if the rotation is valid, false otherwise.
bool game::check_rotation_valid()
{
    std::pair<int, int> pointOne = _currentPiece->get_one();            // Get the components to check against the new point
    std::pair<int, int> pointTwo = _currentPiece->get_two();
    std::pair<int, int> pointThree = _currentPiece->get_three();
    std::pair<int, int> pointFour = _currentPiece->get_four();

    _currentPiece->rotate();                                            // Perform rotation (will rotate back on collision)

    std::pair<int, int> updatedPointOne = _currentPiece->get_one();		// Get updated components after rotation
    std::pair<int, int> updatedPointTwo = _currentPiece->get_two();
    std::pair<int, int> updatedPointThree = _currentPiece->get_three();
    std::pair<int, int> updatedPointFour = _currentPiece->get_four();

    if (inside_bucket(updatedPointOne) && inside_bucket(updatedPointTwo)
                                       && inside_bucket(updatedPointThree)
                                       && inside_bucket(updatedPointFour))
    {
        if (_b.check_position_filled(updatedPointOne))
        {
            if (!(updatedPointOne == pointOne || updatedPointOne == pointTwo || updatedPointOne == pointThree || updatedPointOne == pointFour))
            {
                _currentPiece->rotate_reverse();                        // Rotate back to original position

                return false;
            }
        }

        if (_b.check_position_filled(updatedPointTwo))
        {
            if (!(updatedPointTwo == pointOne || updatedPointTwo == pointTwo || updatedPointTwo == pointThree || updatedPointTwo == pointFour))
            {
                _currentPiece->rotate_reverse();                        // Rotate back to original position

                return false;
            }
        }

        if (_b.check_position_filled(updatedPointThree))
        {
            if (!(updatedPointThree == pointOne || updatedPointThree == pointTwo || updatedPointThree == pointThree || updatedPointThree == pointFour))
            {
                _currentPiece->rotate_reverse();                        // Rotate back to original position

                return false;
            }
        }

            if (_b.check_position_filled(updatedPointFour))
        {
            if (!(updatedPointFour == pointOne || updatedPointFour == pointTwo || updatedPointFour == pointThree || updatedPointFour == pointFour))
            {
                _currentPiece->rotate_reverse();                        // Rotate back to original position

                return false;
            }
        }

        _currentPiece->rotate_reverse();                                // Rotate back to original position

        return true;
    }

    _currentPiece->rotate_reverse();                                    // Rotate back to original position

    return false;
}

// Check if the input point is inside the "bucket" of the board
// The bucket will be defined as within the U shaped container of the
// board. Within the left, right, and bottom walls. Rotations allow
// portions of pieces to be non-visible above the top of the board.
// Returns true if the point is within the bucket, false otherwise
bool game::inside_bucket(std::pair<int, int> & point)
{
    int first = point.first;
    int second = point.second;

    if (first >= 0 && first < BOARD_WIDTH)
    {
        if (second < BOARD_HEIGHT)
        {
            return true;
        }
    }

    return false;
}

// Remove the current piece from the board
// Used in conjunction with place current piece after a piece's location
// has been updated
void game::remove_current_piece()
{
    _b.unfill_position(_currentPiece->get_one());		// Error checked in unfill function
    _b.unfill_position(_currentPiece->get_two());
    _b.unfill_position(_currentPiece->get_three());
    _b.unfill_position(_currentPiece->get_four());
}

// Place the current piece on the board
// Used in conjunction with remove current piece after a piece has been removed
// from the board
// Returns false if there is a collision, true otherwise.
void game::place_current_piece()
{
    int value = _currentPiece->get_type();

    _b.fill_position(_currentPiece->get_one(), value);		// Error checked in unfill function
    _b.fill_position(_currentPiece->get_two(), value);
    _b.fill_position(_currentPiece->get_three(), value);
    _b.fill_position(_currentPiece->get_four(), value);
}

// Move the current piece in the specified direciton (integer).
// First, perform a collision check on potentially moving the current piece in
// the specfied direciton. If valid, removes the current piece from the board,
// update the position of the piece, and then places the piece on the board.
// Returns true if the move is successful, false otherwise.
bool game::move_piece(int direction)
{
    if (check_movement_valid(direction))
    {
        remove_current_piece();

        if (direction == LEFT)
        {
            _currentPiece->move_left();
        }
        else if (direction == RIGHT)
        {
            _currentPiece->move_right();
        }
        else if (direction == DOWN)
        {
            _currentPiece->move_down();
        }
        else // ERROR
        {
            return false;
        }

        place_current_piece();

        return true;
    }

    return false;
}

// Rotate the current piece 90 degrees clockwise
// First, perform a collision check on potentially rotating the current piece 90 degrees
// clockwise. If valid, removes the current piece from the board, updates the position
// of the piece, and then places the piece on the board.
// Returns true if the move is successful, false otherwise
bool game::rotate_piece()
{
    if (check_rotation_valid())
    {
        remove_current_piece();

        _currentPiece->rotate();

        place_current_piece();

        return true;
    }

    return false;
}

// Generate a random piece from the 7 possible Tetris pieces
// This function represents generating the first piece of the game.
// The secondary generation takes into account the previous piece,
// to bias away from generating the same piece twice in a row.
piece * game::generate_piece()
{
    srand(time(nullptr));
    int pieceIndex = rand()	% MAX_PIECES;

    if (pieceIndex == 0)
    {
        i * p = new i();
        return p;
    }
    else if (pieceIndex == 1)
    {
        j * p = new j();
        return p;
    }
    else if (pieceIndex == 2)
    {
        l * p = new l();
        return p;
    }
    else if (pieceIndex == 3)
    {
        o * p = new o();
        return p;
    }
    else if (pieceIndex == 4)
    {
        s * p = new s();
        return p;
    }
    else if (pieceIndex == 5)
    {
        t * p = new t();
        return p;
    }
    else	// ROLL SIX
    {
        z * p = new z();
        return p;
    }
}

// Generate a secondary piece representing the next piece field in the game
// The second piece is biased against rolling the same piece twice in a row,
// where an initial roll of 8 results in a reroll, as well as the same piece twice
// in a row.
piece * game::generate_piece(piece * previous)
{
    srand(time(nullptr));
    int pieceIndex = rand() % (MAX_PIECES + 1);

    if (pieceIndex == 0)
    {
        i * p = new i();
        if (p == dynamic_cast<i*>(previous))
        {
            p = nullptr; delete p;
            return generate_piece();
        }
        return p;
    }
    else if (pieceIndex == 1)
    {
        j * p = new j();
        if (p == dynamic_cast<j*>(previous))
        {
            p = nullptr; delete p;
            return generate_piece();
        }
        return p;
    }
    else if (pieceIndex == 2)
    {
        l * p = new l();
        if (p == dynamic_cast<l*>(previous))
        {
            p = nullptr; delete p;
            return generate_piece();
        }
        return p;
    }
    else if (pieceIndex == 3)
    {
        o * p = new o();
        if (p == dynamic_cast<o*>(previous))
        {
            p = nullptr; delete p;
            return generate_piece();
        }
        return p;
    }
    else if (pieceIndex == 4)
    {
        s * p = new s();
        if (p == dynamic_cast<s*>(previous))
        {
            p = nullptr; delete p;
            return generate_piece();
        }
        return p;
    }
    else if (pieceIndex == 5)
    {
        t * p = new t();
        if (p == dynamic_cast<t*>(previous))
        {
            p = nullptr; delete p;
            return generate_piece();
        }
        return p;
    }
    else if (pieceIndex == 6)
    {
        z * p = new z();
        if (p == dynamic_cast<z*>(previous))
        {
            p = nullptr; delete p;
            return generate_piece();
        }
        return p;
    }
    else	// REROLL
    {
        return generate_piece();
    }
}

// Get next piece
// Return pointer to next piece in queue
piece * game::get_next_piece()
{
    return _nextPiece;
}
