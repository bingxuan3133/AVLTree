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
	Node *newParent;
	if(parent->balance == +2 && parent->rightChild->balance == +1) {
		parent->balance = 0;
		parent->rightChild->balance = 0;
	} else if(parent->balance == +2 && parent->rightChild->balance == +2) {
		parent->balance = -1;
		parent->rightChild->balance = 0;
	} else if(parent->balance == +2 && parent->rightChild->balance == 0) {
		parent->balance = +1;
		parent->rightChild->balance = -1;
	} else if(parent->balance == +1 && parent->rightChild->balance == +1) {
		parent->balance = -1;
		parent->rightChild->balance = -1;		
	} else if(parent->balance == +1 && parent->rightChild->balance == -1) {
		parent->balance = 0;
		parent->rightChild->balance = -2;
	} else if(parent->balance == +1 && parent->rightChild->balance == 0) {
		parent->balance = 0;
		parent->rightChild->balance = -1;
	}
	
	newParent = parent->rightChild;
		
	parent->rightChild = NULL;
	
	if(newParent->leftChild != NULL)
		parent->rightChild = newParent->leftChild;
	
	newParent->leftChild = parent;

	return newParent;
}

Node *rightRotate(Node *parent) {
	Node *newParent;
	if(parent->balance == -2 && parent->leftChild->balance == -1) {
		parent->balance = 0;
		parent->leftChild->balance = 0;
	} else if(parent->balance == -2 && parent->leftChild->balance == -2) {
		parent->balance = +1;
		parent->leftChild->balance = 0;
	} else if(parent->balance == -2 && parent->leftChild->balance == 0) {
		parent->balance = -1;
		parent->leftChild->balance = +1;
	} else if(parent->balance == -1 && parent->leftChild->balance == -1) {
		parent->balance = +1;
		parent->leftChild->balance = +1;		
	} else if(parent->balance == -1 && parent->leftChild->balance == +1) {
		parent->balance = 0;
		parent->leftChild->balance = +2;
	} else if(parent->balance == -1 && parent->leftChild->balance == 0) {
		parent->balance = 0;
		parent->leftChild->balance = +1;
	}
	
	newParent = parent->leftChild;
	
	parent->leftChild = NULL;
	
	if(newParent->rightChild != NULL)
		parent->leftChild = newParent->rightChild;	
	
	newParent->rightChild = parent;
	
	return newParent;
}

Node *doubleLeftRotate(Node *parent) {
	Node *newParent;
	parent->rightChild = rightRotate(parent->rightChild);
	newParent = leftRotate(parent);

	return newParent;
}

Node *doubleRightRotate(Node *parent) {
	Node *newParent;
	
	parent->leftChild = leftRotate(parent->leftChild);
	newParent = rightRotate(parent);

	return newParent;
}






