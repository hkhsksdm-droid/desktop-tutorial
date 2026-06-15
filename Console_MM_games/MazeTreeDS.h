#pragma once

	// Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
	using namespace std;

	class MazeTreeDS
	{
	public:
		class Node;
		Node* root = nullptr;

		class Node {

		public:
			int value;
			Node* left;
			Node* right;
			Node(int value, Node* left = nullptr, Node* right = nullptr) {
				this->value = value;
				this->left = left;
				this->right = right;
			}
		};

		void insert(Node*& node, int value)
		{
			//base case of recursion
			if (node == nullptr) {
				node = new Node(value);
				return;
			}
			//ignore duplicates
			if (node->value == value) return;

			//
			if (value < node->value)
				insert(node->left, value);
			else
				insert(node->right, value);


		}

		int min(Node* node) {
			if (node == nullptr) throw exception("Empty tree");
			if (node->left == nullptr) return node->value;
			return min(node->left);
		}

		int max(Node* node) {
			if (node == nullptr) throw exception("Empty tree");
			if (node->right == nullptr) return node->value;
			return max(node->right);
		}


		void traverseInOrder(Node* node) {
			if (node == nullptr) return;
			traverseInOrder(node->left);
			cout << node->value << " ";
			traverseInOrder(node->right);
		}
		void traversePreOrder(Node* node) {
			if (node == nullptr) return;
			cout << node->value << " ";
			traversePreOrder(node->left);
			traversePreOrder(node->right);
		}
		void traversePostOrder(Node* node) {
			if (node == nullptr) return;
			traversePostOrder(node->left);
			traversePostOrder(node->right);
			cout << node->value << " ";
		}


		bool exists(Node* node, int value) {
			//not found base case
			if (node == nullptr) return false;
			//found base case
			if (node->value == value) return true;
			//recurse: continue searching left or right subtree
			if (value < node->value)
				return exists(node->left, value);
			else
				return exists(node->right, value);
		}

	public:
		void insert(int value) { insert(root, value); }
		int min() { return min(root); }
		int max() { return max(root); }
		void traverseInOrder() { traverseInOrder(root); }
		void traversePreOrder() { traversePreOrder(root); }
		void traversePostOrder() { traversePostOrder(root); }
		bool exists(int value) { return exists(root, value); }
	};


//
//int main()
//	{
//		MazeTreeDS t;
//		int nums[] = { 5, 1, 4, 2, 3, 6, 10, 7, 9, 8 };
//		for (auto n : nums)
//			t.insert(n);
//
//		cout << "Min: " << t.min() << endl;
//		cout << "Max: " << t.max() << endl;
//
//		cout << "4 exists? " << t.exists(4) << endl;
//		cout << "11 exists? " << t.exists(11) << endl;
//
//		cout << "PreOrder: ";
//		t.traversePreOrder();
//		cout << endl;
//
//		cout << "PostOrder: ";
//		t.traversePostOrder();
//		cout << endl;
//
//		cout << "InOrder: ";
//		t.traverseInOrder();
//		cout << endl;
//	}
