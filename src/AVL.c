#include "Rotation.h"
#include "AVL.h"
#include <stdio.h>

Node *avlAdd(Node *root, Node *nodeToAdd) {
	int balanceBefore;

	if(root == NULL) { // Reach NULL
		root = nodeToAdd;
	} else { // Compare
		if(nodeToAdd->data < root->data) { // Go to Left
		
		printf("%i go left\n", nodeToAdd->data);
		
			if(root->leftChild == NULL) { // leftChild is empty
				root->leftChild = avlAdd(root->leftChild, nodeToAdd);
				root->balance--;
			} else {
				balanceBefore = root->leftChild->balance;
				root->leftChild = avlAdd(root->leftChild, nodeToAdd);
				if(root->leftChild->balance - balanceBefore != 0 && root->leftChild->balance != 0) // did the depth of leftChild changed?
					root->balance--;
			}
			
			
		} else if(nodeToAdd->data > root->data) { // Go to Right
		
		printf("%i go right\n", nodeToAdd->data);
		
			if(root->rightChild == NULL) { // rightChild is empty
				root->rightChild = avlAdd(root->rightChild, nodeToAdd);
				root->balance++;
			} else {
				balanceBefore = root->rightChild->balance;
				root->rightChild = avlAdd(root->rightChild, nodeToAdd);
				if(root->rightChild->balance - balanceBefore != 0 && root->rightChild->balance != 0) // did the depth of rightChild changed?
					root->balance++;
			}
			
		} else { // Equal
			printf("error\n");
		}
	}
	
	// Rotation
	if(root->balance == 2) {
		if(root->rightChild->balance >= 0 ) {
			root = leftRotate(root);
			printf("it rotated left\n");
		} else {
			root = doubleLeftRotate(root);
			printf("it double rotated left\n");
		}
		
	} else if(root->balance == -2) {
		if(root->leftChild->balance <= 0 ) {
			root = rightRotate(root);
			printf("it rotated right\n");
		} else {
			root = doubleLeftRotate(root);
			printf("it double rotated left\n");
		}
	}
	
	return root;
}