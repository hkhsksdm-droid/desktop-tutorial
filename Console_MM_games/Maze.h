
#pragma once
#include <iostream>
#include "MazeTreeDS.h"
#include <vector>
#include <iomanip>
class Maze
{
public:
	
	MazeTreeDS t;
	
	void drawMaze()
	{
		//drawMaze0();

	}

	friend std::ostream& operator<<(std::ostream& os, const Maze& maze);
	
	vector<vector<int>> Map = {
	{ 6, 10, 12 },
	{ 5,  0,  5 },
	{ 3, 10,  9 }
	};

    vector<vector<int>> Map1 = {
    {  38, 10, 12,  6, 12 },
    {  3, 12,  7, 13,  5 },
    {  6, 11, 29,  5,  5 },
    {  5,  6, 11,  9,  5 },
    {  3, 11, 10, 10,  9 }
    };
	//choose map by setting myMap to the map you want to use. Map1 is the default map.
    vector<vector<int>> myMap = Map1;

    //  +---+---+---+---+---+
    //  | ^         |       |
    //  +   +---+   +   +   +
    //  |       |       |   |
    //  +---+   +   +   +   +
    //  |         * |   |   |
    //  +   +---+   +   +   +
    //  |   |           |   |
    //  +   +   +---+---+   +
    //  |                   |
    //  +---+---+---+---+---+

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


    Node* moveRight(Node* currentRoom, std::string& msg) {
		return t.moveRight(currentRoom, msg);
    }
    Node* moveLeft(Node* currentRoom, std::string& msg) {
		return t.moveLeft(currentRoom, msg);
    }
    Node* moveUp(Node* currentRoom, std::string& msg) {
		return t.moveUp(currentRoom, msg);
    }
    Node* moveDown(Node* currentRoom, std::string& msg) {
		return t.moveDown(currentRoom, msg);
    }















    //remember to learn this
	// << op overload for printing the maze to the console
    friend std::ostream& operator << (std::ostream& os, Maze& maze) {
        // Loop through rows (y)
        for (size_t y = 0; y < maze.t.grid.size(); ++y) {

            // --- 1. PRINT THE TOP WALLS OF THE ENTIRE ROW ---
            for (size_t x = 0; x < maze.t.grid[y].size(); ++x) {
                os << "+"; // Corner pillar

                int cell = maze.t.grid[y][x]->boxTypeID;
                // If bit 1 (Top) is 0, draw a wall. Otherwise, leave it open for a path.
                if ((cell & 1) == 0) os << "---";
                else os << "   ";
            }
            os << "+\n"; // Cap off the row with a final corner and drop to the next line

            // --- 2. PRINT THE LEFT WALLS AND INSIDE ROOMS ---
            for (size_t x = 0; x < maze.t.grid[y].size(); ++x) {
                int cell = maze.t.grid[y][x]->boxTypeID;

                // If bit 8 (Left) is 0, draw a wall.
                if ((cell & 8) == 0) os << "|";
                else os << " ";

                // 2. Draw the inside of the room
            // Use Bitwise AND to check if the 16 bit is turned on!
                if ((cell & 32) != 0 ) {
                    os << " ^ "; // Draw a star in the middle of the room
                }
                else if ((cell & 16) != 0) {
                    os << " * ";
                }
                else {
                    os << "   "; // Draw an empty 3-space floor
                }
            }

            // Print the final Right wall for the very last room in the row
            int lastCell = maze.t.grid[y].back()->boxTypeID;
            if ((lastCell & 2) == 0) os << "|\n";
            else os << " \n";
        }

        // --- 3. PRINT THE VERY BOTTOM FLOOR OF THE MAZE ---
        size_t lastY = maze.t.grid.size() - 1;
        for (size_t x = 0; x < maze.t.grid[lastY].size(); ++x) {
            os << "+";
            int cell = maze.t.grid[lastY][x]->boxTypeID;

            // If bit 4 (Bottom) is 0, draw a wall.
            if ((cell & 4) == 0) os << "---";
            else os << "   ";
        }
        os << "+\n"; // The final bottom-right corner

        return os;
    }


    Node* getStartNode() {
        // Returns the pointer to the top-left room
        return t.getStartNode();
    }

    void printDebugMap() {
        std::cout << "--- MAZE DEBUG MAP ---\n";

        // Loop through the rows (y)
        for (size_t y = 0; y < myMap.size(); ++y) {

            // Loop through the columns (x)
            for (size_t x = 0; x < myMap[y].size(); ++x) {

                // setw(3) forces every number to take up exactly 3 spaces of width.
                // This guarantees the columns line up perfectly!
                std::cout << std::setw(3) << t.grid[y][x]->boxTypeID << " ";
            }

            // Drop to the next line at the end of the row
            std::cout << "\n";
        }
        std::cout << "----------------------\n";
    }
};
//(cell & 8) == 0
//  1 0 1 0   (This is the room : Decimal 10)
//& 1 0 0 0   (This is the mask : Decimal 8, checking for the Left door)
//-------- -
//= 1 0 0 0   (The result is Decimal 8!)
// Bitwise AND is a great way to check if a specific door exists in a room. If the result of the AND operation is equal to the mask, then that door exists.


//size_t: universal C++ tool used for measuring the size of anything in memory. flexible, portable, and safe. It is an unsigned integer type that can represent the size of any object in memory, making it suitable for indexing and counting elements in containers.
//if 32bit system fit 32bit, if 64bit fit 64bit. int only fit 32bit.