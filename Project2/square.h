#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include "path.h"

/**
 * Class representing a square.
 * This is only used for the internals of the maze.
 * You can ignore this class.
 */
class Square
{
	private:

    		vector<bool> _walls;		// Information for adjacent squares
		bool _visited;			// Flag for if square is visited
		int _row;			// Row in maze
		int _col;			// Column in maze
    		int _distance;			// Minimum distance from start to square, -1 default value (unvisited)
    		int _height;			// Height of room
		Square * _parent;		// Pointer to previous square (in path)
	public:
		
    		//The default square is completely isolated.
    		Square() : _walls(4,false), _visited(false), _row(0), _col(0), _distance(-1), _height(0), _parent(NULL)
		{
		}

    		Square(int height) : _walls(4,false), _visited(false), _row(0), _col(0), _distance(-1), _height(height), _parent(NULL)
		{
		}

    		Square(const Square & s) : _walls(s._walls), _visited(s._visited), _row(s._row), _col(s._col), _distance(s._distance), _height(s._height), _parent(s._parent)
		{
		}

		~Square()
		{
			_parent = NULL;
			delete _parent;
		}

    		// Used for setting up the maze.
    		// Set's the boarders for the square.
    		void set_dir(bool val, int dir)
		{
			_walls[dir] = val;
		}

    		void set_height(int height)
		{
			_height = height;
		}

    		// check if you can go in any of these directions.
    		bool can_go_dir(int dir) const
		{
			return _walls[dir];
		}

		// Get the visited flag
		bool visited() const
		{
			return _visited;
		}

		// Set the visited flag to true
		void set_visited()
		{
			_visited = true;
		}

		// Set the row to input
		void set_row(int row)
		{
			_row = row;
		}

		// Set the column to input
		void set_col(int col)
		{
			_col = col;
		}

		// Get the row field
		int get_row()
		{
			return _row;
		}

		// Get the col field
		int get_col()
		{
			return _col;
		}

		// Get the (minimum) distance from the starting position
		// **USED IN THE DIJKSTRA ALGORITHM**
		int get_distance()
		{
			return _distance;
		}

		// Set the distance field for the square
		// Represents the (minimum) distance from the starting position
		void set_distance(int distance)
		{
			_distance = distance;
		}

		// Return the height of the room
		// **USED IN CALCULATION OF TRAVEL TIME BETWEEN ROOMS**
    		int height() const
		{
			return _height;
		}

		Square * get_parent()
		{
			return _parent;
		}

		void set_parent(Square * parent)
		{
			_parent = parent;
		}
};

#endif // SQUARE_H
