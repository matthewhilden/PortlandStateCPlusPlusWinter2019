#include "maze.h"
#include "path.h"
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <tuple>
#include <utility>
#include <iostream>
#include <climits>
#include <sstream>

using namespace std;

path solve_dfs(Maze & m, int rows, int cols, point startPoint, point endPoint);
path solve_bfs(Maze & m, int rows, int cols, point startPoint, point endPoint);
path solve_dijkstra(Maze & m, int rows, int cols, point startPoint, point endPoint);
path construct_path(Square * square);

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
		     << endl;
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

	point startPoint = make_pair(0, 0);						// Made these since the three algorithms all use (0,0) and (rows - 1, cols - 1)
	point endPoint = make_pair(rows - 1, cols - 1);					// even though my parameters allow for changing these

    	if(opt == "-dfs")
    	{
        	// solve the maze
        	cout << "\nSolved dfs" << endl;
        	path p = solve_dfs(m, rows, cols, startPoint, endPoint);
        	m.print_maze_with_path(cout, p, false, false, startPoint, endPoint);
    	}

    	if(opt == "-bfs")
    	{
        	cout << "\nSolved bfs" << endl;
        	path p = solve_bfs(m, rows, cols, startPoint, endPoint);
        	m.print_maze_with_path(cout, p, false, false, startPoint, endPoint);
    	}

    	if(opt == "-dij")
    	{
        	cout << "\nSolved dijkstra" << endl;
        	path p = solve_dijkstra(m, rows, cols, startPoint, endPoint);
        	m.print_maze_with_path(cout, p, true, false, startPoint, endPoint);
    	}
}

// Find a path from the beginning of the maze to the end
// The DFS algorithm exhausts a single path before backtracking to the next potential path. 
path solve_dfs(Maze & m, int rows, int cols, point startPoint, point endPoint)
{
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

	return construct_path(m.get_square(endPoint));
}

// Find a path from the beginning of the maze to the end of the maze
// The BFS algorithm simultaneously exhausts one position forward in all possible paths through the maze
path solve_bfs(Maze & m, int rows, int cols, point startPoint, point endPoint)
{
	Square * currentSquare = m.get_square(startPoint);
	Square * endSquare = m.get_square(endPoint);
	
	queue<Square *> squares;
	squares.push(currentSquare);
	
	while (!squares.empty())											// An empty stack denotes that there are no unvisited
	{														// maze squares left to exhaust
		currentSquare = squares.front();
		squares.pop();
		currentSquare->set_visited();
		
		if (currentSquare->can_go_dir(LEFT))
		{
			point leftPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(LEFT);
			Square * leftSquare = m.get_square(leftPoint);

			if (!leftSquare->visited())									// If the adjacent square is already visited, we have already added
			{												// the square to the stack, and would be duplicate work
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

	return construct_path(m.get_square(endPoint));
}

// Structure for defining operator comparison for items used in a priority queue
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

// Implementation of Dijkstra's algorithm for finding the shortest path through the maze
// Dijkstra's algorithm finds the shortest path between the start point and end point,
// using a modified BFS algorithm. The algorithm selects an unvisited square and sets all adjacent squares'
// distance field to the calculated values. If the calculated distance to the adjacent square is less than its
// current distance field, the value is overridden with the smaller value. The algorithm chooses the closest
// adjacent square and continues the search. This algorithm is exhausted until all squares in the maze are visited.
path solve_dijkstra(Maze & m, int rows, int cols, point startPoint, point endPoint)
{
	priority_queue<Square *, vector<Square *>, orderByDistance> allSquares;

	allSquares.push(m.get_square(startPoint));

	while (!allSquares.empty())											// An empty stack denotes that there are no unvisited
	{														// maze squares left to exhaust
		Square * currentSquare = allSquares.top();
		allSquares.pop();

		if (currentSquare->can_go_dir(LEFT))
		{
			point leftPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(LEFT);
			Square * leftSquare = m.get_square(leftPoint);
			
			if (!leftSquare->visited())									// I do not want to put a square back into the
			{												// queue if it has already processed
				if (leftSquare->get_distance() == DEFAULT_DISTANCE)
				{
					int cost = abs(currentSquare->height() - leftSquare->height());			// If the distance is unchanged from its initialized value
					leftSquare->set_distance(currentSquare->get_distance() + cost);			// of -1, the distance will always be updated
					leftSquare->set_parent(currentSquare);
					allSquares.push(leftSquare);
				}
				else
				{
					int currentDistance = currentSquare->get_distance();
					int updatedCost = abs(currentSquare->height() - leftSquare->height());
					if (currentDistance + updatedCost < leftSquare->get_distance())
					{
						leftSquare->set_distance(currentDistance + updatedCost);		// The distance is only changed if the calculated new value
						leftSquare->set_parent(currentSquare);					// is less (shorter) than the current distance
						allSquares.push(leftSquare);
					}
				}
			}
		}

		if (currentSquare->can_go_dir(UP))									// I chose not to push these duplicated sections into a
		{													// method because of a high number of input parameters
			point upPoint = make_pair(currentSquare->get_row(), currentSquare->get_col()) + moveIn(UP);	// and the fact that I am pushing to my queue
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

	return construct_path(m.get_square(endPoint));
}

// Construct the path through the maze
// Constructs the path by backtracking from the end of the maze
// traversing through the parent squares of the current square
path construct_path(Square * square)
{
	list<point> path;

	while (square->get_parent() != NULL)								// The initial square in the maze does not have a parent
	{												// so a NULL check is sufficient
		path.push_front(make_pair(square->get_row(), square->get_col()));
		square = square->get_parent();
	}

	path.push_front(make_pair(0, 0));
	return path;
}
