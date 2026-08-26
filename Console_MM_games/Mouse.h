#pragma once
#include <iostream>
#include <string>
#include "Maze.h"    // Include Maze instead of MazeTreeDS so we can draw it!
#include <thread> // Replaces windows.h
#include <chrono> // Replaces windows.h
class Mouse
{
	public:
		bool solveDFS(Node* currentRoom, Maze& MazeThe, std::string& msg, char& mouseFacing, int& totalCost) {

			if (currentRoom == nullptr) return false;
			if (currentRoom->visited == true) return false;

			// CHALK MARK: Mark the room as visited
			currentRoom->visited = true;

			// ==========================================
			// ANIMATION FRAME: Redraw the screen!
			// ==========================================
			std::cout << "\x1b[2J\x1b[H"; // Clear the screen
			std::cout << "--- AI AUTOPILOT ACTIVE ---\n";
			std::cout << MazeThe;         // Draw the physical maze
			std::cout << "Battery Cost: " << totalCost << "\n";
			std::cout << msg;
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
			// ==========================================

			// DID WE WIN?
			if (currentRoom->isStar == true) {
				msg = "\n*** Maze Solved! Found the star! ***\n";
				return true;
			}

			// --- TRY UP ---
	// PEEK FIRST: Is there a door? And is the room unvisited?
			if (currentRoom->top != nullptr && currentRoom->top->visited == false) {

				// Safe to drive!
				Node* nextRoom = MazeThe.t.moveUp(currentRoom, msg, mouseFacing, totalCost);

				if (solveDFS(nextRoom, MazeThe, msg, mouseFacing, totalCost)) return true;

				// BACKTRACK
				MazeThe.t.moveDown(nextRoom, msg, mouseFacing, totalCost);
			}

			// --- TRY RIGHT ---
			if (currentRoom->right != nullptr && currentRoom->right->visited == false) {

				Node* nextRoom = MazeThe.t.moveRight(currentRoom, msg, mouseFacing, totalCost);

				if (solveDFS(nextRoom, MazeThe, msg, mouseFacing, totalCost)) return true;

				MazeThe.t.moveLeft(nextRoom, msg, mouseFacing, totalCost);
			}

			// --- TRY DOWN ---
			if (currentRoom->bottom != nullptr && currentRoom->bottom->visited == false) {

				Node* nextRoom = MazeThe.t.moveDown(currentRoom, msg, mouseFacing, totalCost);

				if (solveDFS(nextRoom, MazeThe, msg, mouseFacing, totalCost)) return true;

				MazeThe.t.moveUp(nextRoom, msg, mouseFacing, totalCost);
			}

			// --- TRY LEFT ---
			if (currentRoom->left != nullptr && currentRoom->left->visited == false) {

				Node* nextRoom = MazeThe.t.moveLeft(currentRoom, msg, mouseFacing, totalCost);

				if (solveDFS(nextRoom, MazeThe, msg, mouseFacing, totalCost)) return true;

				MazeThe.t.moveRight(nextRoom, msg, mouseFacing, totalCost);
			}

			// DEAD END
			return false;
		}


      
};

