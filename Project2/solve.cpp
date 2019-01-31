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
	map<point, point> childToParent;					// Mapping a point to its parent point in the maze
	stack<point> points;							// to maintain information for the path (solution)
	Square * s;

	point start = make_pair(0, 0);
	point finish = make_pair(rows - 1, cols - 1);
	Square * destination = m.get_square(finish);

	points.push(start);							// Require pushing the initial square in the maze to
										// the stack so that the while condiditonal is satisfied
	
	while (!points.empty() && !destination->visited())			// Exhaustive search; traverse until destination
	{
		point current = points.top();
		points.pop();

		s = m.get_square(current);

		if (!s->visited())						// A square may only be visited one time through the traversal
		{
			s->set_visited();

			if (s->can_go_dir(LEFT))				// Check all possible directions for an adjacent square
			{
				point next = current + moveIn(LEFT);
				points.push(next);
				childToParent.insert({next, current});
			}

			if (s->can_go_dir(UP))
			{
				point next = current + moveIn(UP);
				points.push(next);
				childToParent.insert({next, current});
			}

			if (s->can_go_dir(RIGHT))
			{
				point next = current + moveIn(RIGHT);
				points.push(next);
				childToParent.insert({next, current});
			}

			if (s->can_go_dir(DOWN))
			{
				point next = current + moveIn(DOWN);
				points.push(next);
				childToParent.insert({next, current});
			}
		}
	}

	list<point> path;
	point current = make_pair(rows - 1, cols - 1);
	path.push_front(current);
	current = childToParent[current];
	
	while (current != start)						// Construct the list of points of the solution path from the
	{									// information regarding the path saved in the map of points
		path.push_front(current);
		current = childToParent[current];
	}

	path.push_front(start);
	return path;
}

// Find a path from the beginning of the maze (0, 0) to (rows - 1, cols - 1)
// The BFS algorithm simultaneously exhausts one position forward in all possible paths through the maze
// INPUT: Takes a reference to a maze object and two integers representing the size of the maze
// OUTPUT: Returns a list of points representing the path of the solution
path solve_bfs(Maze& m, int rows, int cols)
{
	map<point, point> childToParent;					// Mapping a point to its parent point in the maze
	queue<point> points;							// to maintain information for the path (solution)
	Square * s;

	point start = make_pair(0, 0);
	point finish = make_pair(rows - 1, cols - 1);
	Square * destination = m.get_square(finish);

	points.push(start);							// Require pushing the initial square in the maze to
										// the stack so that the while condiditonal is satisfied

	while (!points.empty() && !destination->visited())			// Exhaustive search; traverse until destination
	{
		point current = points.front();
		points.pop();

		s = m.get_square(current);

		if (!s->visited())						// A square may only be visited one time through the traversal
		{
			s->set_visited();

			if (s->can_go_dir(LEFT))				// Check all possible directions for an adjacent square
			{
				point next = current + moveIn(LEFT);
				points.push(next);
				childToParent.insert({next, current});
			}

			if (s->can_go_dir(UP))
			{
				point next = current + moveIn(UP);
				points.push(next);
				childToParent.insert({next, current});
			}

			if (s->can_go_dir(RIGHT))
			{
				point next = current + moveIn(RIGHT);
				points.push(next);
				childToParent.insert({next, current});
			}

			if (s->can_go_dir(DOWN))
			{
				point next = current + moveIn(DOWN);
				points.push(next);
				childToParent.insert({next, current});
			}
		}
	}

	list<point> path;
	point current = make_pair(rows - 1, cols - 1);
	path.push_front(current);
	current = childToParent[current];
	
	while (current != start)						// Construct the list of points of the solution path from the
	{									// information regarding the path saved in the map of points
		path.push_front(current);
		current = childToParent[current];
	}

	path.push_front(start);
	return path;
}

path solve_dijkstra(Maze& m, int rows, int cols)
{
    return list<point>();
}

path solve_tour(Maze& m, int rows, int cols)
{
    return list<point>();
}
