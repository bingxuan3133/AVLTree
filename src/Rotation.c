#include "Rotation.h"
#include <stdio.h>

Node *leftRotate(Node *parent) {
	Node *newParent = parent->rightChild;
	
	newParent->leftChild = parent;
	
	newParent->rank = 0;
	newParent->leftChild->rank = 0;
	newParent->rightChild->rank = 0;
	
	return newParent;
}

Node *rightRotate(Node *parent) {
	Node *newParent = parent->leftChild;
	
	newParent->rightChild = parent;
	
	newParent->rank = 0;
	newParent->leftChild->rank = 0;
	newParent->rightChild->rank = 0;
	
	return newParent;
}

Node *doubleLeftRotate(Node *parent) {
	Node *newParent = parent->rightChild->leftChild;
	
	newParent->leftChild = parent;
	newParent->rightChild = parent->rightChild;
	
	newParent->rank = 0;
	newParent->leftChild->rank = 0;
	newParent->rightChild->rank = 0;
	
	return newParent;
}

Node *doubleRightRotate(Node *parent) {
	Node *newParent = parent->leftChild->rightChild;
	
	newParent->rightChild = parent;
	newParent->leftChild = parent->leftChild;
	
	newParent->rank = 0;
	newParent->leftChild->rank = 0;
	newParent->rightChild->rank = 0;
	
	return newParent;
}






