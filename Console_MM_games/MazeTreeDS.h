#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GridBoxType.h"
#include <random>
	using namespace std;

	class MazeTreeDS
	{
	public:

	Node* root = nullptr;
	vector<vector<Node*>> grid;

		void linkHorizontal(Node* leftRoom, Node* rightRoom) {
			if (leftRoom != nullptr) leftRoom->right = rightRoom;
			if (rightRoom != nullptr) rightRoom->left = leftRoom;
		}

		void linkVertical(Node* topRoom, Node* bottomRoom) {
			if (topRoom != nullptr) topRoom->bottom = bottomRoom;
			if (bottomRoom != nullptr) bottomRoom->top = topRoom;
		}

	void buildGrid(const vector<vector<int>>& blueprint) {
		if (blueprint.empty() || blueprint[0].empty()) {
			std::cout << "CRASH WARNING: Blueprint is empty!" << std::endl;
			return;
		}
			int rows = blueprint.size();
			int cols = blueprint[0].size();

			// 1. Create a 2D vector (Master Grid) to temporarily hold our pointers
	grid = vector<vector<Node*>> (rows, vector<Node*>(cols));

			for (int r = 0; r < rows; r++) {
				for (int c = 0; c < cols; c++) {
					// We give the Node its unique ID, AND its boxTypeID from your map!
					grid[r][c] = new Node((r * 10) + c, blueprint[r][c]);
				}
			}

			// BITMASK RULES:
			// Top = 1, Right = 2, Bottom = 4, Left = 8

			for (int r = 0; r < rows; r++) {
				for (int c = 0; c < cols; c++) {
					int currentBox = blueprint[r][c];

					// Link East (Right)
					if (c < cols - 1) {
						int eastBox = blueprint[r][c + 1];

						// Rule: Current box MUST have a Right exit (2) 
						// AND the East box MUST have a Left exit (8)
						if ((currentBox & 2) != 0 && (eastBox & 8) != 0) {
							linkHorizontal(grid[r][c], grid[r][c + 1]);
						}
					}

					// Link South (Bottom)
					if (r < rows - 1) {
						int southBox = blueprint[r + 1][c];

						// Rule: Current box MUST have a Bottom exit (4) 
						// AND the South box MUST have a Top exit (1)
						if ((currentBox & 4) != 0 && (southBox & 1) != 0) {
							linkVertical(grid[r][c], grid[r + 1][c]);
						}
					}

				}
			}
			root = grid[0][0];
		}



		//MOVEMENT FUNCTIONS also handle costs and direction changes
//=================================================================================================================
		Node* moveRight(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
			// 1. Check if there is actually a door here
			if (currentRoom->right != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->right->toggleMouse(); // Draw in new room

				if (mouseFacing != ' ' && mouseFacing != 'd') {
					totalCost += 2;
				}
				mouseFacing = 'd'; // Update our physical direction

				// 3. ROOM COST: Add the cost of the new room
				totalCost += currentRoom->right->cost;

				msg = "Mouse moved RIGHT!\n";

				return currentRoom->right;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			totalCost += 1; // You hit a wall, pay the tax!
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}

		Node* moveLeft(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
			// 1. Check if there is actually a door here
			if (currentRoom->left != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->left->toggleMouse(); // Draw in new room

				if (mouseFacing != ' ' && mouseFacing != 'a') {
					totalCost += 2;
				}
				mouseFacing = 'a'; // Update our physical direction

				// 3. ROOM COST: Add the cost of the new room
				totalCost += currentRoom->left->cost;

				msg = "Mouse moved LEFT!\n";

				return currentRoom->left;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			totalCost += 1; // You hit a wall, pay the tax!
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}


		Node* moveUp(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
			// 1. Check if there is actually a door here
			if (currentRoom->top != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->top->toggleMouse(); // Draw in new room

				if (mouseFacing != ' ' && mouseFacing != 'w') {
					totalCost += 2;
				}
				mouseFacing = 'w'; // Update our physical direction

				// 3. ROOM COST: Add the cost of the new room
				totalCost += currentRoom->top->cost;

				msg = "Mouse moved UP!\n";

				return currentRoom->top;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			totalCost += 1; // You hit a wall, pay the tax!
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}

		Node* moveDown(Node* currentRoom, std::string& msg, char& mouseFacing, int& totalCost) {
			// 1. Check if there is actually a door here
			if (currentRoom->bottom != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->bottom	->toggleMouse(); // Draw in new room

				if (mouseFacing != ' ' && mouseFacing != 's') {
					totalCost += 2;
				}
				mouseFacing = 's'; // Update our physical direction

				// 3. ROOM COST: Add the cost of the new room
				totalCost += currentRoom->bottom->cost;

				msg = "Mouse moved DOWN!\n";

				return currentRoom->bottom;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			totalCost += 1; // You hit a wall, pay the tax!
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}
//=================================================================================================================
		
		void updateCost(Node* mouseLocation, Node* oldLocation, char input, int& totalCost, MazeTreeDS& MazeThe) {
			
		}

		int getCost(Node* node) {
			if (node == nullptr) return -1; // or throw an exception
			return node->getCost();
		}


		void traversePreOrder(Node* node) {
			if (node == nullptr) return;
			cout << node->BlockID << " ";
			traversePreOrder(node->left);
			traversePreOrder(node->right);
		}
		void traversePostOrder(Node* node) {
			if (node == nullptr) return;
			traversePostOrder(node->left);
			traversePostOrder(node->right);
			cout << node->BlockID << " ";
		}


		bool exists(Node* node, int BlockID) {
			//not found base case
			if (node == nullptr) return false;
			//found base case
			if (node->BlockID == BlockID) return true;
			//recurse: continue searching left or right subtree
			if (BlockID < node->BlockID)
				return exists(node->left, BlockID);
			else
				return exists(node->right, BlockID);
		}
		Node* getStartNode() {
			// Returns the pointer to the top-left room
			return root;
		}


		//meme
		Node* buildBigMaze() {
			const int ROWS = 10;
			const int COLS = 10;

			int layout[ROWS][COLS] = {
				{ 0, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
				{ 2, 2, 1, 2, 1, 2, 2, 2, 2, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 },
				{ 1, 2, 2, 2, 2, 2, 2, 1, 2, 1 },
				{ 1, 1, 1, 1, 1, 2, 1, 1, 1, 1 },
				{ 2, 2, 2, 2, 1, 2, 1, 2, 2, 2 },
				{ 1, 1, 1, 1, 1, 2, 1, 1, 1, 1 },
				{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 },
				{ 2, 2, 2, 2, 2, 2, 2, 1, 1, 3 }
			};

			// 1. Resize the class member 'grid' properly!
			grid = vector<vector<Node*>>(ROWS, vector<Node*>(COLS, nullptr));
			int blockCounter = 1;

			// 2. FIRST PASS: Create the rooms and put them into the member grid
			for (int r = 0; r < ROWS; r++) {
				for (int c = 0; c < COLS; c++) {
					if (layout[r][c] == 2) {
						grid[r][c] = nullptr; // Wall
					}
					else {
						grid[r][c] = new Node(blockCounter, 1);
						grid[r][c]->BlockID = blockCounter++;
						grid[r][c]->cost = 5;

						if (layout[r][c] == 0) {
							grid[r][c]->isMouse = true;
							root = grid[r][c];
						}
						if (layout[r][c] == 3) {
							grid[r][c]->isStar = true;
						}
					}
				}
			}

			// 3. SECOND PASS: Link the doors using the member grid
			for (int r = 0; r < ROWS; r++) {
				for (int c = 0; c < COLS; c++) {
					if (grid[r][c] != nullptr) {
						if (r > 0 && grid[r - 1][c] != nullptr) grid[r][c]->top = grid[r - 1][c];
						if (r < ROWS - 1 && grid[r + 1][c] != nullptr) grid[r][c]->bottom = grid[r + 1][c];
						if (c > 0 && grid[r][c - 1] != nullptr) grid[r][c]->left = grid[r][c - 1];
						if (c < COLS - 1 && grid[r][c + 1] != nullptr) grid[r][c]->right = grid[r][c + 1];
					}
				}
			}
			return root;
		}

		Node* buildDynamicMaze(int rows, int cols) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distrib(0, 15);

			// 1. Initialize map with basic random walls/doors
			std::vector<std::vector<int>> newMap(rows, std::vector<int>(cols, 0));

			for (int r = 0; r < rows; r++) {
				for (int c = 0; c < cols; c++) {
					int mask = distrib(gen);

					// Clean up borders
					if (r == 0) mask &= ~1;
					if (c == cols - 1) mask &= ~2;
					if (r == rows - 1) mask &= ~4;
					if (c == 0) mask &= ~8;

					newMap[r][c] = mask;
				}
			}

			// 2. GUARANTEED PATH CARVING
			int currR = 0;
			int currC = 0;
			while (currR < rows - 1 || currC < cols - 1) {
				if (currR < rows - 1 && (currC == cols - 1 || distrib(gen) % 2 == 0)) {
					newMap[currR][currC] |= 4;
					newMap[currR + 1][currC] |= 1;
					currR++;
				}
				else if (currC < cols - 1) {
					newMap[currR][currC] |= 2;
					newMap[currR][currC + 1] |= 8;
					currC++;
				}
			}

			// 3. SPECIAL BLOCKS: Place the Star at the bottom-right corner (Bit 32)
			// Add a mouse flag or starting bit to the top-left cell [0][0] 
			// (Using bit 16 or 32 depending on how your Node constructor checks the mouse flag)
			newMap[0][0] |= 16;

			// Place the Star at the bottom-right corner (Bit 32)
			newMap[rows - 1][cols - 1] |= 32;

			// 4. Build the grid using your engine
			buildGrid(newMap);

			// 5. Explicitly flag the Mouse (Start) and Star (Finish) nodes
			if (root != nullptr) {
				root->isStar = true;       // Top-left is now the star
				root->isMouse = false;
				root->boxTypeID |= 16;
			}

			if (!grid.empty() && !grid.back().empty()) {
				Node* bottomTheRight = grid.back().back();
				if (bottomTheRight != nullptr) {
					bottomTheRight->isStar = true;
					bottomTheRight->boxTypeID |= 32;
				}
			}

			return root;
		}

		//Node* buildDynamicMaze(int rows, int cols) {
		//	// 1. Generate the open map blueprint
		//	std::vector<std::vector<int>> newMap(rows, std::vector<int>(cols, 15));

		//	for (int r = 0; r < rows; r++) {
		//		for (int c = 0; c < cols; c++) {
		//			int mask = 0;
		//			if (r > 0) mask |= 1;           // Open Top
		//			if (c < cols - 1) mask |= 2;    // Open Right
		//			if (r < rows - 1) mask |= 4;    // Open Bottom
		//			if (c > 0) mask |= 8;           // Open Left

		//			newMap[r][c] = mask;
		//		}
		//	}

		//	buildGrid(newMap);
		//	return root;
		//}


		std::string toStringNodeObject(Node* node) {
			return node->toString();
		}






	public:
		
		void traversePreOrder() { traversePreOrder(root); }
		void traversePostOrder() { traversePostOrder(root); }
		bool exists(int BlockID) { return exists(root, BlockID); }
	};
