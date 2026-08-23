#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GridBoxType.h"

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



		//MOVEMENT FUNCTIONS
//=================================================================================================================
		Node* moveRight(Node* currentRoom, std::string& msg) {
			// 1. Check if there is actually a door here
			if (currentRoom->right != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->right->toggleMouse(); // Draw in new room

				msg = "Mouse moved RIGHT!\n";

				return currentRoom->right;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}

		Node* moveLeft(Node* currentRoom, std::string& msg) {
			// 1. Check if there is actually a door here
			if (currentRoom->left != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->left->toggleMouse(); // Draw in new room

				msg = "Mouse moved LEFT!\n";

				return currentRoom->left;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}

		Node* moveUp(Node* currentRoom, std::string& msg) {
			// 1. Check if there is actually a door here
			if (currentRoom->top != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->top->toggleMouse(); // Draw in new room

				msg = "Mouse moved UP!\n";

				return currentRoom->top;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}

		Node* moveDown(Node* currentRoom, std::string& msg) {
			// 1. Check if there is actually a door here
			if (currentRoom->bottom != nullptr) {

				currentRoom->toggleMouse();        // Erase from old room
				currentRoom->bottom	->toggleMouse(); // Draw in new room

				msg = "Mouse moved DOWN!\n";

				return currentRoom->bottom;         // <-- Hand back the new room!
			}

			// 2. If it is a wall (nullptr), the mouse doesn't move.
			msg = "Ouch! You hit a wall.\n";
			return currentRoom;                    // <-- Hand back the exact same room
		}
//=================================================================================================================




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

	public:
		
		void traversePreOrder() { traversePreOrder(root); }
		void traversePostOrder() { traversePostOrder(root); }
		bool exists(int BlockID) { return exists(root, BlockID); }
	};
