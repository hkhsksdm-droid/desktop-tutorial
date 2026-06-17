	#pragma once
#pragma once
#include <iostream>
#include "MazeTreeDS.h"
#include <vector>

class Maze
{
public:
	Maze()
	{

	}

	
	void drawMaze()
	{
		drawMaze0();

	}

	friend std::ostream& operator<<(std::ostream& os, const Maze& maze);
	
	vector <vector<int>> maze = {
		{ 1, 0, 1, 1, 1 },
		{ 1, 0, 1, 0, 1 },
		{ 1, 1, 1, 0, 1 },
		{ 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1 }
	};

	 // int[] should be turn into GridBoxType Data type 
	std::vector<int> PrintMaze(const std::vector<int>& maze)
	{
		std::vector<int> result;

		for (auto n : maze)
		{
			// 1. Print the current number
			std::cout << n << " ";

			// 2. Add it to our return vector (if you need to pass data back)
			result.push_back(n);
		}
		std::cout << std::endl;

		return result; // Matches the vector<int> return type
	};



	void drawMaze0(std::ostream& os)
	{
		MazeTreeDS t;
		int nums[] = { 5, 1, 4, 2, 3, 6, 10, 7, 9, 8 };
		for (auto n : nums)
			t.insert(n);

		// IF USING OPTION 1 (Vector):
		std::vector<int> numsVec = { 5, 1, 4, 2, 3, 6, 10, 7, 9, 8 };
		std::vector<int> printedData = PrintMaze(numsVec);

		// IF USING OPTION 2 (Raw Array):
		//std::vector<int> printedData = PrintMaze(nums, 10); // Pass array and its size (10)
		
		cout << "Min: " << t.min() << endl;
		cout << "Max: " << t.max() << endl;

		cout << "4 exists? " << t.exists(4) << endl;
		cout << "11 exists? " << t.exists(11) << endl;

		cout << "PreOrder: ";
		t.traversePreOrder();
		cout << endl;

		cout << "PostOrder: ";
		t.traversePostOrder();
		cout << endl;

		cout << "InOrder: ";
		t.traverseInOrder();
		cout << endl;
	}
};

	inline std::ostream& operator << (std::ostream& os, const Maze& maze) {
		maze.drawMaze0(os);

		
		// Loop through rows and columns of your private grid matrix
		//for (size_t y = 0; y < maze.grid.size(); ++y) {
		//	for (size_t x = 0; x < maze.grid[y].size(); ++x) {

		//		// Customize what prints based on your data values
		//		if (maze.grid[y][x] == 1) {
		//			os << "██"; // Wall character
		//		}
		//		else {
		//			os << "  "; // Empty path space
		//		}
		//	}
		//	os << "\n"; // New line at the end of every row
		//}
		return os; // Return the stream so you can chain commands together
	}

