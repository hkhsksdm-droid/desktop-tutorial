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


add 16 for a star block
add 32 for mouse position

*/
class Node {

public:
	int BlockID;
	int boxTypeID;
	int cost;
	bool isStar = false;
	bool isMouse = false;
	bool visited = false;
	Node* left;
	Node* right;
	Node* top;
	Node* bottom;

	Node(
		int BlockID, 
		int blockTypeID, 
		int cost = 5,
		bool isStar = false, 
		bool isMouse = false, 
		bool visited = false,
		Node* left = nullptr, 
		Node* right = nullptr, 
		Node* top = nullptr, 
		Node* bottom = nullptr) 
	
	
	{
		this->BlockID = BlockID;
		this->boxTypeID = blockTypeID;
		this->cost = cost;
		this->isStar = isStar;       
		this->isMouse = isMouse;    
		this->visited = visited;
		this->BlockID = blockTypeID & 15;
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
		


		if ((blockTypeID & 16) != 0) {
			this->isStar = true;
		}

		if ((blockTypeID & 32) != 0) {
			this->isMouse = true;
		}

		int baseRoomType = blockTypeID & 15;

		if (baseRoomType == 3 || 
			baseRoomType == 6 || 
			baseRoomType == 9 || 
			baseRoomType == 12) {

			this->cost = 7; // FIXED: Overwrite the class variable, don't create a new 'int'
		}

		if (this->BlockID == 0) { //starting block cost 0 to move out of
			this->cost = 0; // Set this to 0, 1, or whatever you prefer!
		}
	}

	int getCost() {
		return this->cost;
	}

	void toggleStar() {
		this->isStar = !this->isStar;           // Flip the boolean
		this->boxTypeID = this->boxTypeID ^ 16; // Toggle the 16 bit in the ID
	}

	void toggleMouse() {
		this->isMouse = !this->isMouse;           // Flip the boolean
		this->boxTypeID = this->boxTypeID ^ 32; // Toggle the 32 bit in the ID
	}

	std::string toString() const{
		std::string info = 
			"Node ID: " + std::to_string(BlockID) +
			" | BoxType: " + std::to_string(boxTypeID) +
			" | Mouse: " + (isMouse ? "Yes" : "No") +
			" | Star: " + (isStar ? "Yes" : "No");
			" | Cost: " + std::to_string(cost) +
			" | Visited: " + (visited ? "Yes" : "No");
			
		return info;

		}
};
//How ^ (XOR)magically fixes this
//
//The XOR operator ( ^ 16) looks specifically at the 16 switch and simply flips it to the opposite of whatever it currently is.
//
//If the star is OFF(10) : 10 ^ 16 acts like addition.It flips the switch ON, resulting in 26.
//
//If the star is ON(26) : 26 ^ 16 acts like subtraction.It flips the switch OFF, resulting back in 10.
//
//By using ^ 16, you safely "toggle" the star back and forth without ever accidentally breaking your door numbers(the 1, 2, 4, and 8)!