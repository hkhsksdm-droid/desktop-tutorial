#include <iostream>
#include <string>
/*
box 1: Dead end 
box 1:
box 1:
box 1:
box 1:
box 1:
box 1:
box 1:
box 1:
*/
class GridBoxType
{
public:
	
	class Box1;
	Box1* root = nullptr;
	
	class Box1 {

	public:
		//there should be an orginating note but also have many
		// other notes that the current note can go to 
		Box1* Before;
		Box1* right;
		Node(int value, Node* left = nullptr, Node* right = nullptr) {
			this->value = value;
			this->left = left;
			this->right = right;
		}
};

	struct GridBoxType
	{
		
	};