#include <iostream>
#include <string>
/*
		Top = 1
		 +----+
Left = 8 |    | Right = 2
		 +----+
		Bottom = 4



			box 0: Block

+----+
|    |	0
+----+

            box 1: Dead end 
+----+
     |	8
+----+

	+-  -+
	|    |	1
	+----+

		+----+
		|		2
		+----+

			+----+
			|    |	4
			+-  -+

            box 2: 2 way path
+-  -+s
|    |	5
+-  -+

	+-  -+
	     |	9
	+----+

		+-  -+
		|		3
		+----+

			+----+
			|		6
			+-  -+

				+----+
				     |	12
				+-  -+
					+----+
							10
					+----+

			box 3: 3 way path
+----+
		14
+-  -+

	+-  -+
		 |	13
	+-  -+

		+-  -+
		|		7
		+-  -+

			+-  -+
					11
			+----+

			box 4: 4 way path

+-  -+
		15
+-  -+


*/
class Node {

public:
	int BlockID;
	int boxTypeID;
	bool isStar = false;
	Node* left;
	Node* right;
	Node* top;
	Node* bottom;
	Node(int BlockID, int blockTypeID, bool isStar = false, Node* left = nullptr, Node* right = nullptr, Node* top = nullptr, Node* bottom = nullptr) {
		this->BlockID = BlockID;
		this->boxTypeID = blockTypeID;
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}
};