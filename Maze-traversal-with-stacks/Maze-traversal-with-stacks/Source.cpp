#include <iostream>
#include <vector>
#include "Stack.h"
using namespace std;

Stack findNeighbours(vector<vector<int>> maze, MazeCoordinate current, int col_size, int row_size)
{
	Stack neighbourList;
	
	current.x++;
	if (current.x <= col_size && maze[current.x][current.y] == 0)
		neighbourList.push(current);
	current.x--;

	current.y++;
	if (current.y <= row_size  && maze[current.x][current.y] == 0)
		neighbourList.push(current);
	current.y--;

	current.x--;
	if (current.x >= 0 && maze[current.x][current.y] == 0)
		neighbourList.push(current);
	current.x++;

	current.y--;
	if (current.y >= 0 && maze[current.x][current.y] == 0)
		neighbourList.push(current);
	current.y++;

	return neighbourList;		// if it returns empty, it means stuck (it is not possible to move any neighbour)
}

int main()
{
	int row_size, col_size;
	cout << "Please enter the row and column number: ";
	cin >> row_size >> col_size;

	int begin_row, begin_col;
	cout << "\nPlease enter the starting point: ";
	cin >> begin_row >> begin_col;

	// maze creation
	vector<vector<int>> maze;
	for (int i = 0; i < col_size; i++)
	{
		vector<int> row;
		for (int j = 0; j < row_size; j++)
		{
			row.push_back(-1);
		}
		maze.push_back(row);
	}

	// filling maze
	int input;
	cout << "\nPlease enter the structure of maze: " << endl;
	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			cin >> maze[j][i];
		}
	}

	// row and column sizes -1 because vectors/arrays start from 0. Do not want to repeat -1 operation everywhere.
	row_size--;
	col_size--;
	MazeCoordinate current(begin_col, begin_row);	// this is current x and y in the coordinate system until the end of the program.
	Stack path(current);							// this Stack contains all the available neighbours that are not used.
	Stack printPath(current);						// this is the corrent solution of the whole problem.
	// loop until finding an exit. Check if x or y is boundary but not the initial point.
	do
	{
		path.pop();
		maze[current.x][current.y] = 2;	// it means it is visited

		Stack freeNeighbours = findNeighbours(maze, current, col_size, row_size);
		if (!freeNeighbours.isEmpty())
		{
			// if there is more than one way to go, all points are stored for further usage in the while loop.
			do
			{
				current = freeNeighbours.topAndPop();
				path.push(current);
			} while (!freeNeighbours.isEmpty());
		}
		else
		{
			// Stuck
			current = path.topAndPop();

			while (printPath.top().x != current.x && printPath.top().y != current.y)
				printPath.pop();
		}
		printPath.push(current);

	} while (!((current.x == col_size || current.y == row_size || current.x == 0 || current.y == 0) && (current.x != begin_col && current.y != begin_row)));

	// reversing stack
	path.makeEmpty();
	do
	{
		path.push(printPath.topAndPop());
	} while (!printPath.isEmpty());

	// print the reversed stack
	while (!path.isEmpty())
	{
		current = path.topAndPop();
		cout << current.y << " " << current.x << endl;
	}

	return 0;
}