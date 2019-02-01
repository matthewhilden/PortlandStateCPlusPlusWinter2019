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
	
	stack<point> points;
	points.push(startPoint);
	
	while (!points.empty() && !endSquare->visited())						// The second conditional ensures we do not continue
	{												// the DFS algorithm after reaching the end square
		point currentPoint = points.top();
		points.pop();

		currentSquare = m.get_square(currentPoint);

		if (!currentSquare->visited())								// Do not want to process the same square twice
		{
			currentSquare->set_visited();
			
			if (currentSquare != endSquare)							// If the end square is found, we can stop adding to the stack
			{
				if (currentSquare->can_go_dir(LEFT))
				{
					point leftPoint = currentPoint + moveIn(LEFT);
					Square * leftSquare = m.get_square(leftPoint);

					if (!leftSquare->visited())					// If the adjacent square is already visited, we have already added
					{								// the square to the stack, and would be duplicate work
						points.push(leftPoint);
						leftSquare->set_parent(currentSquare);
					}
				}

				if (currentSquare->can_go_dir(UP))
				{
					point upPoint = currentPoint + moveIn(UP);
					Square * upSquare = m.get_square(upPoint);

					if (!upSquare->visited())
					{
						points.push(upPoint);
						upSquare->set_parent(currentSquare);
					}
				}
	
				if (currentSquare->can_go_dir(RIGHT))
				{
					point rightPoint = currentPoint + moveIn(RIGHT);
					Square * rightSquare = m.get_square(rightPoint);

					if(!rightSquare->visited())
					{
						points.push(rightPoint);
						rightSquare->set_parent(currentSquare);
					}
				}
	
				if (currentSquare->can_go_dir(DOWN))
				{
					point downPoint = currentPoint + moveIn(DOWN);
					Square * downSquare = m.get_square(downPoint);

					if (!downSquare->visited())
					{
						points.push(downPoint);
						downSquare->set_parent(currentSquare);
					}
				}
			}
		}
	}
	
	list<point> path;
	Square * square = m.get_square(endPoint);

	while (square->get_parent() != NULL)								// The initial square in the maze does not have a parent
	{												// so we know when we are at the beginning of the maze
		path.push_front(make_pair(square->get_row(), square->get_col()));
		square = square->get_parent();
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
	
	queue<point> points;
	points.push(startPoint);
	
	while (!points.empty() && !endSquare->visited())						// The second conditional ensures we do not continue
	{												// the BFS algorithm after reaching the end square
		point currentPoint = points.front();
		points.pop();

		currentSquare = m.get_square(currentPoint);

		if (!currentSquare->visited())								// Do not want to process the same square twice
		{
			currentSquare->set_visited();
			
			if (currentSquare != endSquare)							// If the end square is found, we can stop adding to the queue
			{
				if (currentSquare->can_go_dir(LEFT))
				{
					point leftPoint = currentPoint + moveIn(LEFT);
					Square * leftSquare = m.get_square(leftPoint);

					if (!leftSquare->visited())					// If the adjacent square is already visited, we have already added
					{								// the square to the queue, and would be duplicate work
						points.push(leftPoint);
						leftSquare->set_parent(currentSquare);
					}
				}

				if (currentSquare->can_go_dir(UP))
				{
					point upPoint = currentPoint + moveIn(UP);
					Square * upSquare = m.get_square(upPoint);

					if (!upSquare->visited())
					{
						points.push(upPoint);
						upSquare->set_parent(currentSquare);
					}
				}
	
				if (currentSquare->can_go_dir(RIGHT))
				{
					point rightPoint = currentPoint + moveIn(RIGHT);
					Square * rightSquare = m.get_square(rightPoint);

					if(!rightSquare->visited())
					{
						points.push(rightPoint);
						rightSquare->set_parent(currentSquare);
					}
				}
	
				if (currentSquare->can_go_dir(DOWN))
				{
					point downPoint = currentPoint + moveIn(DOWN);
					Square * downSquare = m.get_square(downPoint);

					if (!downSquare->visited())
					{
						points.push(downPoint);
						downSquare->set_parent(currentSquare);
					}
				}
			}
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

// Construct the list of points of the solution path from the
// Implementation of Dijkstra's algorithm for finding the shortest path through the maze
// Dijkstra's algorithm finds the shortest path between the starting square and all other squares in the maze
// using a modified BFS algorithm. The algorithm selects an unvisited square and sets all adjacent squares'
// distance field to the calculated values. If the calculated distance to the adjacent square is less than its
// current distance field, the value is overridden with the smaller value. This algorithm is exhausted until all squares
// in the maze are visited.
path solve_dijkstra(Maze& m, int rows, int cols)
{
	// 1. Add all squares to a set
	// 2. For each square in the set, update distances of all adjacent squares, update parent
	// 3. Trace backwards using parent node information to construct list
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
		
		}
	}


    	return list<point>();
}

path solve_tour(Maze& m, int rows, int cols)
{
    return list<point>();
}
