#pragma once
#include <iostream>
#include <stdio.h>
#include <conio.h>// for _getch() window only 
#include "Maze.h"
class MicroMouseApp
{
public:
	string msg;
	MicroMouseApp()
	{
		
	}

	void run()
	{
		while (!std::cin.eof())
		{
			std::cout << "Micro mouse app running...\n";
			
			runGameLoop();
			clearScreen();
		}
	}

	void runGameLoop()
	{	
		Maze MazeThe;
		Node* mouseLocation = MazeThe.getStartNode();
		bool running = true;
		msg = "";

		while (running) {
			printMaze(MazeThe);
			
			char input = _getch(); // Read a single character instantly

			switch (input) {
			case 'w':
				mouseLocation = MazeThe.moveUp(mouseLocation, msg);
				break;

			case 's':
				mouseLocation = MazeThe.moveDown(mouseLocation, msg);
				break;

			case 'a':
				mouseLocation = MazeThe.moveLeft(mouseLocation, msg);
				break;

			case 'd':
				mouseLocation = MazeThe.moveRight(mouseLocation, msg);
				break;

			case 'q':
			case 'Q':
				running = false;
				break;
			}
			clearScreen();
		}
	}


	void printMaze(Maze MazeThe)
	{
		std::cout << "Creating maze...\n";
		std::cout << MazeThe << std::endl;
		std::cout << "Debugging maze...\n";
		MazeThe.printDebugMap();
		std::cout << "Use W/A/S/D to move. Press Q to quit.\n";
		std::cout << msg;
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



