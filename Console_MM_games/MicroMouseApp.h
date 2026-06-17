#pragma once
#include <iostream>
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
		}
	}



	void createMaze()
	{
		std::cout << "Creating maze...\n"	;
		Maze MazeThe;
		std::cout << MazeThe << std::endl;
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


};



