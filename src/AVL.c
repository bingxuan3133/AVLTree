#include "Rotation.h"
#include "AVL.h"
#include <stdio.h>

Node *avlAdd(Node *root, Node *nodeToAdd) {
	int balanceBefore;

	if(root == NULL) { // Reach NULL
		root = nodeToAdd;
		root->balance = 0;
	} else { // Compare
		if(nodeToAdd->data < root->data) { // Go to Left

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
		} else {
			root = doubleLeftRotate(root);
		}
		
	} else if(root->balance == -2) {
		if(root->leftChild->balance <= 0 ) {
			root = rightRotate(root);
		} else {
			root = doubleRightRotate(root);
		}
	}

	return root;
}

Node *avlRemove(Node **ptrToRoot, Node *nodeToRemove) {
	if(nodeToRemove == NULL) {
		return NULL;
	} else if(nodeToRemove->data == (*ptrToRoot)->data) {
		
		if((*ptrToRoot)->leftChild != NULL)
			*ptrToRoot = avlGetReplacer(&(*ptrToRoot)->leftChild);
		else if((*ptrToRoot)->rightChild != NULL)
			*ptrToRoot = (*ptrToRoot)->rightChild;
		else
			*ptrToRoot = NULL;

		return nodeToRemove;
	} else {
	
		if(nodeToRemove->data < (*ptrToRoot)->data) {
			avlRemove(&(*ptrToRoot)->leftChild, nodeToRemove);
		} else if(nodeToRemove->data > (*ptrToRoot)->data) {
			avlRemove(&(*ptrToRoot)->rightChild, nodeToRemove);
		} else {
			printf("error");
		}
		
	}
	
	return nodeToRemove;
}

Node *avlGetReplacer(Node **ptrToRoot) {
	Node *replacer;
	int balanceBefore;
  
	if((*ptrToRoot)->rightChild != NULL) { // Keep on going
    balanceBefore = (*ptrToRoot)->rightChild->balance;
    
		replacer = avlGetReplacer(&(*ptrToRoot)->rightChild);
    
		if((*ptrToRoot)->rightChild == NULL) {
      (*ptrToRoot)->balance--;
    } else {
      if(balanceBefore != 0 && (*ptrToRoot)->rightChild->balance == 0) // did the depth of rightChild changed?
        (*ptrToRoot)->balance--;
    }
    
	} else { // Found re-placer
  
		replacer = *ptrToRoot;
		if((*ptrToRoot)->leftChild != NULL) {
			*ptrToRoot = (*ptrToRoot)->leftChild;
		} else {
			*ptrToRoot = NULL;
    }
  }
  
  replacer->leftChild = NULL;
  replacer->rightChild = NULL;
  replacer->balance = 0;

	// Rotation
  if((*ptrToRoot) != NULL) {
    if((*ptrToRoot)->balance == 2) {
      if((*ptrToRoot)->rightChild->balance >= 0 ) {
        (*ptrToRoot) = leftRotate((*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleLeftRotate((*ptrToRoot));
      }
      
    } else if((*ptrToRoot)->balance == -2) {
      if((*ptrToRoot)->leftChild->balance <= 0 ) {
        (*ptrToRoot) = rightRotate((*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleRightRotate((*ptrToRoot));
      }
    }
  }
  
	return replacer;
}
