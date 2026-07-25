
#pragma once
#include <iostream>
#include "MazeTreeDS.h"
#include <vector>

class Maze
{
public:
	
	MazeTreeDS t;
	
	void drawMaze()
	{
		//drawMaze0();

	}

	friend std::ostream& operator<<(std::ostream& os, const Maze& maze);
	
	vector<vector<int>> myMap = {
	{ 6, 10, 12 },
	{ 5,  0,  5 },
	{ 3, 10,  9 }
	};

	 // int[] should be turn into GridBoxType Data type 
	//std::vector<int> PrintMaze(const std::vector<int>& maze)
	//{
	//	std::vector<int> result;

	//	for (auto n : maze)
	//	{
	//		// 1. Print the current number
	//		std::cout << n << " ";

	//		// 2. Add it to our return vector (if you need to pass data back)
	//		result.push_back(n);
	//	}
	//	std::cout << std::endl;

	//	return result; // Matches the vector<int> return type
	//};

	Maze()
	{
		// Build the physical pointers automatically when the Maze is created!
		t.buildGrid(myMap);
	}

	
	friend std::ostream& operator << (std::ostream& os,  Maze& maze) {
		//maze.drawMaze0(os);

		
		// Loop through rows (y) and columns (x) of the bitmask map
		for (size_t y = 0; y < maze.myMap.size(); ++y) {
			for (size_t x = 0; x < maze.myMap[y].size(); ++x) {

				// If it is exactly 0, it's a solid wall.
				if (maze.myMap[y][x] == 0) {
					os << 
						"+----+"
						"|    |"	
						"+----+ "
						;
				}
				// Otherwise (if it's 1-15), it's a walkable path room!
				else {
					os << "00";
				}
			}
			os << "\n"; // New line at the end of every row
		}
		return os; // Return the stream so you can chain commands together
	}
};

