
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

	
    friend std::ostream& operator << (std::ostream& os, Maze& maze) {
        // Loop through rows (y)
        for (size_t y = 0; y < maze.myMap.size(); ++y) {

            // --- 1. PRINT THE TOP WALLS OF THE ENTIRE ROW ---
            for (size_t x = 0; x < maze.myMap[y].size(); ++x) {
                os << "+"; // Corner pillar

                int cell = maze.myMap[y][x];
                // If bit 1 (Top) is 0, draw a wall. Otherwise, leave it open for a path.
                if ((cell & 1) == 0) os << "---";
                else os << "   ";
            }
            os << "+\n"; // Cap off the row with a final corner and drop to the next line

            // --- 2. PRINT THE LEFT WALLS AND INSIDE ROOMS ---
            for (size_t x = 0; x < maze.myMap[y].size(); ++x) {
                int cell = maze.myMap[y][x];

                // If bit 8 (Left) is 0, draw a wall.
                if ((cell & 8) == 0) os << "|";
                else os << " ";

                os << "   "; // 3 spaces for the inside of the room
            }

            // Print the final Right wall for the very last room in the row
            int lastCell = maze.myMap[y].back();
            if ((lastCell & 2) == 0) os << "|\n";
            else os << " \n";
        }

        // --- 3. PRINT THE VERY BOTTOM FLOOR OF THE MAZE ---
        size_t lastY = maze.myMap.size() - 1;
        for (size_t x = 0; x < maze.myMap[lastY].size(); ++x) {
            os << "+";
            int cell = maze.myMap[lastY][x];

            // If bit 4 (Bottom) is 0, draw a wall.
            if ((cell & 4) == 0) os << "---";
            else os << "   ";
        }
        os << "+\n"; // The final bottom-right corner

        return os;
    }
};
//  1 0 1 0   (This is the room : Decimal 10)
//& 1 0 0 0   (This is the mask : Decimal 8, checking for the Left door)
//-------- -
//= 1 0 0 0   (The result is Decimal 8!)
