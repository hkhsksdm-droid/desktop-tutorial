#pragma once
#include <iostream>
#include <stdio.h>
#include <conio.h>// for _getch() window only 
#include "Maze.h"
class MicroMouseApp
{
public:
	MicroMouseApp()
	{
		
	}

	void run()
	{
		while (!std::cin.eof())
		{
			std::cout << "Micro mouse app running...\n";
			createMaze();
			ReadKey();
		}
	}



	void createMaze()
	{
		Maze MazeThe;
		std::cout << "Creating maze...\n";
		std::cout << MazeThe << std::endl;
		std::cout << "Debugging maze...\n";
		MazeThe.printDebugMap();
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



