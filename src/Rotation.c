#include "Rotation.h"
#include <stdio.h>

int getHeight(Node *parent) {
	int leftHeight = 0, rightHeight = 0;

	if(parent->leftChild == NULL && parent->rightChild == NULL)
		return 1;
	else if(parent->leftChild == NULL)
		rightHeight = _getHeight(parent->rightChild);
	else if(parent->rightChild == NULL)
		leftHeight = _getHeight(parent->leftChild);
	else {
		leftHeight = _getHeight(parent->leftChild);
		rightHeight = _getHeight(parent->rightChild);
	}
	
	if(leftHeight >= rightHeight)
		return leftHeight+1;
	else
		return rightHeight+1;
}

Node *leftRotate(Node *parent) {
	Node *newParent = parent->rightChild;

	if(newParent->leftChild != NULL)
		parent->rightChild = newParent->leftChild;
	
	newParent->leftChild = parent;
	
	newParent->rank += -1;
	newParent->leftChild->rank += -2;
	
	return newParent;
}

Node *rightRotate(Node *parent) {
	Node *newParent = parent->leftChild;
	
	if(newParent->rightChild != NULL)
		parent->leftChild = newParent->rightChild;	
		
	newParent->rightChild = parent;
	
	newParent->rank += 1;
	newParent->rightChild->rank += 2;
	
	return newParent;
}

Node *doubleLeftRotate(Node *parent) {
	Node *newParent = parent->rightChild->leftChild;
	
	newParent->leftChild = parent;
	newParent->rightChild = parent->rightChild;
	
	newParent->leftChild->rank += -2;
	newParent->rightChild->rank += 1;
	
	return newParent;
}

Node *doubleRightRotate(Node *parent) {
	Node *newParent = parent->leftChild->rightChild;
	
	newParent->rightChild = parent;
	newParent->leftChild = parent->leftChild;
	
	newParent->leftChild->rank += -1;
	newParent->rightChild->rank += 2;
	
	return newParent;
}






