#pragma once
#include <iostream>
#include <stdio.h>
#include <conio.h>// for _getch() window only 
#include "Maze.h"
#include "Mouse.h"
class MicroMouseApp
{
public:
	string msg;
	int totalCost = 0;
	char mouseFacing = ' '; // Default facing direction is 'down'
	MicroMouseApp()
	{
		
	}

	void run()
	{
		while (!std::cin.eof())
		{
			std::cout << "Micro mouse app running...\n";
			
			runGameLoop();
			std::cout << "Total cost: " << totalCost << std::endl;
			std::cout << msg << std::endl;
			ReadKey();
			totalCost = 0; // Reset total cost for the next run
			clearScreen();
		}
	}

	void runGameLoop()
	{	
		Maze MazeThe;
		//Node* mouseLocation = MazeThe.buildDynamicMaze(10, 10);
		//Node* mouseLocation = MazeThe.buildBigMaze();
		//vector<vector<int>> bigLayout = {}; // your 10x10 layout
		//Node* mouseLocation = MazeThe.setMaze(bigLayout);
		//Node* mouseLocation = MazeThe.getStartNode();
		Node* mouseLocation = MazeThe.getStartNode();
		bool running = true;
		msg = "";

		while (running) {
			printMaze(MazeThe, mouseLocation);
			printCost(mouseLocation, MazeThe);

			mouseLocation = changeMovementInput(mouseLocation, MazeThe, running);

			
			clearScreen();
			if (mouseLocation->isStar == true) {
				msg = "\n*** Maze Solved! Found the star! ***\n";
				printMaze(MazeThe, mouseLocation);
				break;
			}
		}
	}

	Node* changeMovementInput(Node* mouseLocation, Maze& MazeThe, bool& running) {
		std::cout << "Use W/A/S/D to move. Press Q to quit.\n";
		std::cout << msg;
		char input = _getch(); // Read a single character instantly
		Node* oldLocation = mouseLocation;

		switch (input) {
		case 'w':
			mouseLocation = MazeThe.moveUp(mouseLocation, msg, mouseFacing, totalCost);
			
			break;

		case 's':
			mouseLocation = MazeThe.moveDown(mouseLocation, msg, mouseFacing, totalCost);
			

			break;

		case 'a':
			mouseLocation = MazeThe.moveLeft(mouseLocation, msg, mouseFacing, totalCost);
			

			break;

		case 'd':
			mouseLocation = MazeThe.moveRight(mouseLocation, msg, mouseFacing, totalCost);
			

			break;

		case 'r':
		case 'R':
			Mouse mouse;
			// Pass in mouseFacing and totalCost!
			mouse.solveDFS(mouseLocation, MazeThe, msg, mouseFacing, totalCost);
			running = false; // End the game loop so we can admire the solved maze!
			break;


		case 'q':
		case 'Q':
			running = false;
			break;
		}


		return mouseLocation;

	}

	void printMaze(Maze& MazeThe, Node* currentRoom )
	{
		std::cout << "The maze...\n";
		std::cout << MazeThe << std::endl;
		std::cout << "Debugging maze...\n";
		MazeThe.printDebugMap();
		std::cout << "Node Data...\n";
		std::cout << MazeThe.toStringNodeObject(currentRoom) << std::endl;
		
	}

	void printCost(Node* currentRoom, Maze& MazeThe) {
		std::cout << "total cost: ";
		std::cout << totalCost << std::endl;
	}

	void solveMaze()
	{
		std::cout << "Solving maze...\n";
	}

	void NavMaze()
	{
		std::cout << "Running test...\n";
	}

	void TheSprint()
	{
		std::cout << "Running real run...\n";
	}




	void displayResults()
	{
		std::cout << "Displaying results...\n";
	}

	void clearScreen()
	{
		std::cout << "\x1b[2J\x1b[H";
	}

	void promptUser()
	{
		std::cout << "Prompting user for input...\n";
	}

	void ReadKey() {
		std::cout << "Press any key to continue..." << std::endl;

		// Reads a single character instantly
		char key = _getch();

		std::cout << "\nYou pressed: " << key << std::endl;
		std::cout << std::endl;
	}
};



