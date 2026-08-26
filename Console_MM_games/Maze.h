
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

	Maze()
	{
		// Build the physical pointers automatically when the Maze is created!
        myMap = Map1;
		t.buildGrid(myMap);
        
	}

    Node* buildBigMaze() {
         return t.buildBigMaze();
    }
    Node* buildDynamicMaze(int rows, int cols) {
         return t.buildDynamicMaze(rows, cols);
    }

    Node* setMaze(vector<vector<int>>& newMap) {
        myMap = newMap;           // 1. Save the new map blueprint
        t.buildGrid(myMap);       // 2. Build the physical node grid using the new map
        return t.getStartNode();  // 3. Return the start node for the mouse   
    }

    Node* getStartNode() {
        // Make sure this is returning the engine's startNode!
        return t.getStartNode();
    }

    Node* moveRight(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
		return t.moveRight(currentRoom, msg, mouseFacing, totalCost);
    }
    Node* moveLeft(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
		return t.moveLeft(currentRoom, msg, mouseFacing, totalCost);
    }
    Node* moveUp(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
		return t.moveUp(currentRoom, msg, mouseFacing, totalCost);
    }
    Node* moveDown(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
		return t.moveDown(currentRoom, msg, mouseFacing, totalCost);
    }



    int getCost(Node* currentRoom) {
		return t.getCost(currentRoom);
    }





    std::string toStringNodeObject(Node* node) {
        return t.toStringNodeObject(node);
    }





    //remember to learn this
	// << op overload for printing the maze to the console
    friend std::ostream& operator << (std::ostream& os, Maze& maze) {
        for (size_t y = 0; y < maze.t.grid.size(); ++y) {

            // --- 1. PRINT TOP WALLS ---
            for (size_t x = 0; x < maze.t.grid[y].size(); ++x) {
                os << "+";
                Node* current = maze.t.grid[y][x];

                // If it's a nullptr (wall), treat it as a solid block
                if (current == nullptr) {
                    os << "---";
                }
                else {
                    int cell = current->boxTypeID;
                    if ((cell & 1) == 0) os << "---";
                    else os << "   ";
                }
            }
            os << "+\n";

            // --- 2. PRINT LEFT WALLS AND ROOMS ---
            for (size_t x = 0; x < maze.t.grid[y].size(); ++x) {
                Node* current = maze.t.grid[y][x];

                if (current == nullptr) {
                    os << "|###"; // Solid wall interior representation
                }
                else {
                    int cell = current->boxTypeID;
                    if ((cell & 8) == 0) os << "|";
                    else os << " ";

                    // Check the explicit engine flags instead of raw bitmasks
                    if (current->isStar) {
                        os << " ^ "; // Print star/finish
                    }
                    else if (current->isMouse) {
                        os << " * "; // Print mouse start
                    }
                    else {
                        os << "   ";
                    }
                }
            }
            os << "|\n";
        }

        // --- 3. PRINT THE VERY BOTTOM FLOOR OF THE MAZE ---
        size_t lastY = maze.t.grid.size() - 1;
        for (size_t x = 0; x < maze.t.grid[lastY].size(); ++x) {
            os << "+";
            Node* current = maze.t.grid[lastY][x];

            // If it's a nullptr (wall), print a solid bottom floor
            if (current == nullptr) {
                os << "---";
            }
            else {
                int cell = current->boxTypeID;
                // If bit 4 (Bottom) is 0, draw a wall.
                if ((cell & 4) == 0) os << "---";
                else os << "   ";
            }
        }
        os << "+\n"; // The final bottom-right corner

        return os;
    }


    void printDebugMap() {
        std::cout << "--- MAZE DEBUG MAP ---\n";

        // Loop through the engine's actual grid dimensions!
        for (size_t y = 0; y < t.grid.size(); ++y) {
            for (size_t x = 0; x < t.grid[y].size(); ++x) {

                // Safely check if the node exists before printing its ID
                if (t.grid[y][x] == nullptr) {
                    std::cout << std::setw(3) << "X" << " "; // Print 'X' for walls
                }
                else {
                    std::cout << std::setw(3) << t.grid[y][x]->boxTypeID << " ";
                }
            }
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