#include "Rotation.h"
#include "AVL.h"
#include <stdio.h>

Node *avlAdd(Node *root, Node *nodeToAdd) {
	if(root == NULL) {
		root = nodeToAdd;
	} else {
		if(nodeToAdd->data < root->data) {
		printf("%i go left\n", nodeToAdd->data);
			root->balance += -1;
			root->leftChild = avlAdd(root->leftChild, nodeToAdd);
			if(root->balance <= -2) {
				root = rightRotate(root);
				printf("rr\n");
			}
		} else if(nodeToAdd->data > root->data) {
		printf("%i go right\n", nodeToAdd->data);
			root->balance += 1;
			root->rightChild = avlAdd(root->rightChild, nodeToAdd);
			if(root->balance >= 2) {
				root = leftRotate(root);
				printf("rl\n");
			}
		} else {
			printf("error");
		}
	}
	
	return root;
}