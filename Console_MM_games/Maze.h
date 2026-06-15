#pragma once
#pragma once
#include <iostream>
#include "MazeTreeDS.h"
class Maze
{
	Maze()
	{

	}

	void drawMaze()
	{
		drawMaze0();

	}

	void drawMaze0()
	{
		MazeTreeDS t;
		int nums[] = { 5, 1, 4, 2, 3, 6, 10, 7, 9, 8 };
		for (auto n : nums)
			t.insert(n);

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


