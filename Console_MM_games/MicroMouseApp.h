#pragma once
#pragma once
class MicroMouseApp
{
public:
	MicroMouseApp();
	{
		//Hello and welcome
	}
	void run();
	{
		while (!std::cin.eof())
		{
			std::cout << "Micro mouse app running...\n";

		}
	}

	void createMaze();
	{
		std::cout << "Creating maze...\n";
		drawMaze();
	}

	void solveMaze();
	{
		std::cout << "Solving maze...\n";
	}

	void NavMaze();
	{
		std::cout << "Running test...\n";
	}

	void TheSprint();
	{
		std::cout << "Running real run...\n";
	}




	void displayResults();
	{
		std::cout << "Displaying results...\n";
	}

	void clearScreen();
	{
		std::cout << "\x1b[2J\x1b[H";
	}

	void promptUser();
	{
		std::cout << "Prompting user for input...\n";
	}


};



