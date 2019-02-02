#include "maze.h"
#include "path.h"
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <list>
#include <tuple>
#include <utility>
#include <iostream>
#include <climits>
#include <sstream>

using namespace std;

path solve_dfs(Maze & m, int rows, int cols);
path solve_bfs(Maze & m, int rows, int cols);
path solve_dijkstra(Maze & m, int rows, int cols);
path solve_tour(Maze & m, int rows, int cols);

const int DEFAULT_DISTANCE = -1;

int main(int argc, char** argv)
{
	if(argc != 4)
    	{
        	cerr << "usage:\n"
                     << "./maze option rows cols\n"
                     << " options:\n"
                     << "  -dfs: depth first search (backtracking)\n"
                     << "  -bfs: breadth first search\n"
                     << "  -dij: dijkstra's algorithm\n"
                     << "  -tour: all corners tour" << endl;
       		return 0;
    	}
    	string opt(argv[1]);

    	int rows, cols;
    	stringstream s;
    	s << argv[2] << " " << argv[3];
    	s >> rows >> cols;

    	// construct a new random maze;
    	Maze m(rows, cols);

    	// print the initial maze out
	cout << "Initial maze" << endl;
   	m.print_maze(cout, opt == "-dij" || opt == "-tour");

    	if(opt == "-dfs")
    	{
        	// solve the maze
        	cout << "\nSolved dfs" << endl;
        	path p = solve_dfs(m, rows, cols);
        	m.print_maze_with_path(cout, p, false, false);
    	}


    	if(opt == "-bfs")
    	{
        	cout << "\nSolved bfs" << endl;
        	path p = solve_bfs(m, rows, cols);
        	m.print_maze_with_path(cout, p, false, false);
    	}

    	if(opt == "-dij")
    	{
        	cout << "\nSolved dijkstra" << endl;
        	path p = solve_dijkstra(m, rows, cols);
        	m.print_maze_with_path(cout, p, true, false);
    	}

    	if(opt == "-tour")
    	{
	        cout << "\nSolved all courners tour" << endl;
        	path p = solve_tour(m, rows, cols);
        	m.print_maze_with_path(cout, p, true, true);
    	}
}

// Find a path from the beginning of the maze (0, 0) to (rows - 1, cols - 1)
// The DFS algorithm exhausts a single path before backtracking to the next potential path. 
// INPUT: Takes a reference to a maze object and two integers representing the size of the maze
// OUTPUT: Returns a list of points representing the path of the solution
path solve_dfs(Maze & m, int rows, int cols)
{
	point startPoint = make_pair(0, 0);
	point endPoint = make_pair(rows - 1, cols - 1);

	Square * currentSquare = m.get_square(startPoint);
	Square * endSquare = m.get_square(endPoint);
	
	stack<Square *> squares;
	squares.push(currentSquare);
	
	while (!squares.empty())								// An empty stack denotes that there are no unvisited
	{											// maze squares left to exhaust
		currentSquare = squares.top();
		squares.pop();
		currentSquare->set_visited();
		
		if (currentSquare->can_go_dir(LEFT))
		{
			point leftPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(LEFT);
			Square * leftSquare = m.get_square(leftPoint);

			if (!leftSquare->visited())						// If the adjacent square is already visited, we have already added
			{									// the square to the stack, and would be duplicate work
				squares.push(leftSquare);
				leftSquare->set_parent(currentSquare);
			}
		}

		if (currentSquare->can_go_dir(UP))
		{
			point upPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(UP);
			Square * upSquare = m.get_square(upPoint);

			if (!upSquare->visited())
			{
				squares.push(upSquare);
				upSquare->set_parent(currentSquare);
			}
		}

		if (currentSquare->can_go_dir(RIGHT))
		{
			point rightPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(RIGHT);
			Square * rightSquare = m.get_square(rightPoint);

			if(!rightSquare->visited())
			{
				squares.push(rightSquare);
				rightSquare->set_parent(currentSquare);
			}
		}

		if (currentSquare->can_go_dir(DOWN))
		{
			point downPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(DOWN);
			Square * downSquare = m.get_square(downPoint);

			if (!downSquare->visited())
			{
				squares.push(downSquare);
				downSquare->set_parent(currentSquare);
			}
		}
	}
	
	list<point> path;
	Square * square = m.get_square(endPoint);

	while (square->get_parent() != NULL)								// The initial square in the maze does not have a parent
	{
		path.push_front(make_pair(square->get_row(), square->get_col()));			// Here we backtrack through the maze to construct the path
		square = square->get_parent();								// by getting parent squares of each square starting at the end
	}

	path.push_front(startPoint);
	return path;
}

// Find a path from the beginning of the maze (0, 0) to (rows - 1, cols - 1)
// The BFS algorithm simultaneously exhausts one position forward in all possible paths through the maze
// INPUT: Takes a reference to a maze object and two integers representing the size of the maze
// OUTPUT: Returns a list of points representing the path of the solution
path solve_bfs(Maze& m, int rows, int cols)
{
	point startPoint = make_pair(0, 0);
	point endPoint = make_pair(rows - 1, cols - 1);

	Square * currentSquare = m.get_square(startPoint);
	Square * endSquare = m.get_square(endPoint);
	
	queue<Square *> squares;
	squares.push(currentSquare);
	
	while (!squares.empty())								// An empty stack denotes that there are no unvisited
	{											// maze squares left to exhaust
		currentSquare = squares.front();
		squares.pop();
		currentSquare->set_visited();
		
		if (currentSquare->can_go_dir(LEFT))
		{
			point leftPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(LEFT);
			Square * leftSquare = m.get_square(leftPoint);

			if (!leftSquare->visited())						// If the adjacent square is already visited, we have already added
			{									// the square to the stack, and would be duplicate work
				squares.push(leftSquare);
				leftSquare->set_parent(currentSquare);
			}
		}

		if (currentSquare->can_go_dir(UP))
		{
			point upPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(UP);
			Square * upSquare = m.get_square(upPoint);

			if (!upSquare->visited())
			{
				squares.push(upSquare);
				upSquare->set_parent(currentSquare);
			}
		}

		if (currentSquare->can_go_dir(RIGHT))
		{
			point rightPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(RIGHT);
			Square * rightSquare = m.get_square(rightPoint);

			if(!rightSquare->visited())
			{
				squares.push(rightSquare);
				rightSquare->set_parent(currentSquare);
			}
		}

		if (currentSquare->can_go_dir(DOWN))
		{
			point downPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(DOWN);
			Square * downSquare = m.get_square(downPoint);

			if (!downSquare->visited())
			{
				squares.push(downSquare);
				downSquare->set_parent(currentSquare);
			}
		}
	}
	
	list<point> path;
	Square * square = m.get_square(endPoint);

	while (square->get_parent() != NULL)								// The initial square in the maze does not have a parent
	{
		path.push_front(make_pair(square->get_row(), square->get_col()));			// Here we backtrack through the maze to construct the path
		square = square->get_parent();								// by getting parent squares of each square starting at the end
	}

	path.push_front(startPoint);
	return path;
}

// Strucutre for defining operator comparison for items used in a priority queue
// Defines a square having closest distance value as being highest priority
struct orderByDistance
{
	bool operator() (Square * s1, Square * s2)
	{
		if (s1->get_distance() > s2->get_distance())
		{
			return true;
		}
		return false;
	}
};



// Construct the list of points of the solution path from the
// Implementation of Dijkstra's algorithm for finding the shortest path through the maze
// Dijkstra's algorithm finds the shortest path between the starting square and all other squares in the maze
// using a modified BFS algorithm. The algorithm selects an unvisited square and sets all adjacent squares'
// distance field to the calculated values. If the calculated distance to the adjacent square is less than its
// current distance field, the value is overridden with the smaller value. This algorithm is exhausted until all squares
// in the maze are visited.
path solve_dijkstra(Maze & m, int rows, int cols)
{
	priority_queue<Square *, vector<Square *>, orderByDistance> allSquares;

	point startPoint = make_pair(0, 0);
	point endPoint = make_pair(rows - 1, cols - 1);

	Square * endSquare = m.get_square(endPoint);
	allSquares.push(m.get_square(startPoint));

	while (!allSquares.empty())
	{
		Square * currentSquare = allSquares.top();
		allSquares.pop();

		if (!currentSquare->visited())
		{
			if (currentSquare->can_go_dir(LEFT))
			{
				point leftPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(LEFT);
				Square * leftSquare = m.get_square(leftPoint);
				
				if (!leftSquare->visited())
				{
					if (leftSquare->get_distance() == DEFAULT_DISTANCE)
					{
						int cost = abs(currentSquare->height() - leftSquare->height());

						leftSquare->set_distance(currentSquare->get_distance() + cost);
						leftSquare->set_parent(currentSquare);
						allSquares.push(leftSquare);
					}
					else
					{
						int currentDistance = currentSquare->get_distance();
						int updatedCost = abs(currentSquare->height() - leftSquare->height());

						if (currentDistance + updatedCost < leftSquare->get_distance())
						{
							leftSquare->set_distance(currentDistance + updatedCost);
							leftSquare->set_parent(currentSquare);
							allSquares.push(leftSquare);
						}
					}
				}
			}

			if (currentSquare->can_go_dir(UP))
			{
				point upPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(UP);
				Square * upSquare = m.get_square(upPoint);
				
				if (!upSquare->visited())
				{
					if (upSquare->get_distance() == DEFAULT_DISTANCE)
					{
						int cost = abs(currentSquare->height() - upSquare->height());

						upSquare->set_distance(currentSquare->get_distance() + cost);
						upSquare->set_parent(currentSquare);
						allSquares.push(upSquare);
					}
					else
					{
						int currentDistance = currentSquare->get_distance();
						int updatedCost = abs(currentSquare->height() - upSquare->height());

						if (currentDistance + updatedCost < upSquare->get_distance())
						{
							upSquare->set_distance(currentDistance + updatedCost);
							upSquare->set_parent(currentSquare);
							allSquares.push(upSquare);
						}
					}
				}
			}

			if (currentSquare->can_go_dir(RIGHT))
			{
				point rightPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(RIGHT);
				Square * rightSquare = m.get_square(rightPoint);

				if (!rightSquare->visited())
				{
					if (rightSquare->get_distance() == DEFAULT_DISTANCE)
					{
						int cost = abs(currentSquare->height() - rightSquare->height());

						rightSquare->set_distance(currentSquare->get_distance() + cost);
						rightSquare->set_parent(currentSquare);
						allSquares.push(rightSquare);
					}
					else
					{
						int currentDistance = currentSquare->get_distance();
						int updatedCost = abs(currentSquare->height() - rightSquare->height());

						if (currentDistance + updatedCost < rightSquare->get_distance())
						{
							rightSquare->set_distance(currentDistance + updatedCost);
							rightSquare->set_parent(currentSquare);
							allSquares.push(rightSquare);
						}
					}
				}
			}

			if (currentSquare->can_go_dir(DOWN))
			{
				point downPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(DOWN);
				Square * downSquare = m.get_square(downPoint);
			
				if (!downSquare->visited())
				{
					if (downSquare->get_distance() == DEFAULT_DISTANCE)
					{
						int cost = abs(currentSquare->height() - downSquare->height());

						downSquare->set_distance(currentSquare->get_distance() + cost);
						downSquare->set_parent(currentSquare);
						allSquares.push(downSquare);
					}
					else
					{
						int currentDistance = currentSquare->get_distance();
						int updatedCost = abs(currentSquare->height() - downSquare->height());
	
						if (currentDistance + updatedCost < downSquare->get_distance())
						{
							downSquare->set_distance(currentDistance + updatedCost);
							downSquare->set_parent(currentSquare);
							allSquares.push(downSquare);
						}
					}
				}
			}
			currentSquare->set_visited();		
		}
	}

	list<point> path;
	Square * square = m.get_square(endPoint);

	while (square->get_parent() != NULL)								// The initial square in the maze does not have a parent
	{												// so a NULL check is sufficient
		path.push_front(make_pair(square->get_row(), square->get_col()));
		square = square->get_parent();
	}

	path.push_front(startPoint);
	return path;
}

path solve_tour(Maze & m, int rows, int cols)
{
	return list<point>();
}
