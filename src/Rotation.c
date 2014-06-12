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
	
	parent->rightChild = NULL;
	
	if(newParent->leftChild != NULL)
		parent->rightChild = newParent->leftChild;
	
	newParent->leftChild = parent;
	
	newParent->rank += -1;
	newParent->leftChild->rank += -2;
	
	return newParent;
}

Node *rightRotate(Node *parent) {
	Node *newParent = parent->leftChild;
	
	parent->leftChild = NULL;
	
	if(newParent->rightChild != NULL)
		parent->leftChild = newParent->rightChild;	
		
	newParent->rightChild = parent;
	
	newParent->rank += 1;
	newParent->rightChild->rank += 2;
	
	return newParent;
}

Node *doubleLeftRotate(Node *parent) {
	Node *temp = parent->rightChild->leftChild;
	Node *newParent;
	
	parent->rightChild->leftChild = NULL;
	temp->rightChild = parent->rightChild;
	parent->rightChild = temp;

	parent->rightChild->rank += 1;
	parent->rightChild->rightChild->rank += 1;
	
	newParent = leftRotate(parent);
	
	return newParent;
}

Node *doubleRightRotate(Node *parent) {
	Node *temp = parent->leftChild->rightChild;
	Node *newParent;
	
	parent->leftChild->rightChild = NULL;
	temp->leftChild = parent->leftChild;
	parent->leftChild = temp;

	parent->leftChild->rank += -1;
	parent->leftChild->leftChild->rank += -1;
	
	newParent = rightRotate(parent);
	
	return newParent;
}






