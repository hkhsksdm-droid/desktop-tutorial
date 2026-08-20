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
			vector<vector<Node*>> grid(rows, vector<Node*>(cols));

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

	public:
		
		void traversePreOrder() { traversePreOrder(root); }
		void traversePostOrder() { traversePostOrder(root); }
		bool exists(int BlockID) { return exists(root, BlockID); }
	};
