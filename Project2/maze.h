#ifndef MAZE_H
#define MAZE_H

#include "square.h"
#include "path.h"
#include <vector>
#include <iostream>

class Maze
{
	private:

		vector<vector<Square>> _squares;
		int _rows;
		int _cols;
		void gen_dfs(vector<vector<bool>> & seen, int r, int c);
		void delete_walls(double frac);
		void set_heights();
		void gen_random_maze();

	public:

		/**
     		* Constructor for Maze class
		* Sets up a new maze that is a grid of rows and columns
     		* The Maze is completely disconnected.
     		* each cell has walls around it.
     		*
     		* @rows number of rows
     		* @cols number of columns
     		*/
    		Maze(int rows, int cols);


		/**
	     	* print out the maze in a human readable format
	     	*/
	    	void print_maze(ostream & out, bool weighted) const;

	    	/**
     		* print the maze while showing the path
     		*/
    		void print_maze_with_path(ostream & out, const path & path, bool weighted, bool tour, point startPoint, point endPoint) const;


    		/**
     		* @return the number of rows in the maze
     		*/
    		int rows() const
		{
			return _rows;
		}

    		/**
     		* @return the number of columns in the maze
     		*/
    		int columns() const
		{
			return _cols;
		}

    		/**
     		* @return if you can go from room (r,c) in direction dir
     		*/
    		bool can_go(int dir, int r, int c) const
		{
			return _squares[r][c].can_go_dir(dir);
		}

    		bool can_go_up(int r, int c) const
		{
			return _squares[r][c].can_go_dir(UP);
		}

    		bool can_go_down(int r, int c) const
		{
			return _squares[r][c].can_go_dir(DOWN);
		}

    		bool can_go_left(int r, int c) const
		{
			return _squares[r][c].can_go_dir(LEFT);
		}

    		bool can_go_right(int r, int c) const
		{
			return _squares[r][c].can_go_dir(RIGHT);
		}

    		/**
     		* @return the cost of moving from room (r,c) in direction dir
     		*/
    		int cost(int r, int c, int dir) const
    		{
        		auto [dr, dc] = moveIn(dir);
       		 	return abs(_squares[r][c].height() - _squares[r + dr][c + dc].height());
    		}

		// Return the square at the specified row and column
		Square * get_square(point p)
		{
			return & _squares[p.first][p.second];
		}
};

/**
 * @return if p is a valid path from (0,0) to specified end point in maze
 */
bool valid_solution(const Maze & m, const path & p, point & startPoint, point & endPoint);

/**
 * @return if p is a valid courners tour in m
 */
bool valid_tour(const Maze & m, const path & p, point & startPoint, point & endPoint);

/**
 * @return if p is a valid path in m
 */
bool valid_path(const Maze & m, const path & p);


#endif // MAZE_H
