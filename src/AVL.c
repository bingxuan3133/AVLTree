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
  int balanceBefore;
  Node *replacer;
  
	if(nodeToRemove == NULL) {
		return NULL;
	} else {
    
    if(*ptrToRoot == NULL) {
      return NULL; // nodeToRemove cannot be found in the tree
      
    } else { // *ptrToRoot is not NULL
      if(nodeToRemove->data == (*ptrToRoot)->data) { // Found nodeToRemove
      
        if((*ptrToRoot)->leftChild != NULL) { // 1st priority on leftChild
        
          printf("NODE%d\n", (*ptrToRoot)->data);
          printf("BALANCE:%d\n", (*ptrToRoot)->balance);
          
          balanceBefore = (*ptrToRoot)->leftChild->balance;
          replacer = avlGetReplacer(&(*ptrToRoot)->leftChild); // get re-placer
          replacer->leftChild = (*ptrToRoot)->leftChild;
          replacer->rightChild = (*ptrToRoot)->rightChild;
          replacer->balance = (*ptrToRoot)->balance;
          *ptrToRoot = replacer;

          if((*ptrToRoot)->leftChild == NULL) // do re-placer has a leftChild?
            (*ptrToRoot)->balance++;
          
          printf("NODE%d\n", (*ptrToRoot)->data);
          printf("BALANCE:%d\n", (*ptrToRoot)->balance);
          
          if((*ptrToRoot)->leftChild != NULL) {
            if(balanceBefore - (*ptrToRoot)->leftChild->balance != 0 && (*ptrToRoot)->leftChild->balance == 0) // did the depth of leftChild changed?
              (*ptrToRoot)->balance++;
          } 
            
        } else if((*ptrToRoot)->rightChild != NULL) { // 2nd priority on rightChild
          *ptrToRoot = (*ptrToRoot)->rightChild;
          
        } else {
          *ptrToRoot = NULL; // no leftChild and rightChild
          
        }
        
      } else if(nodeToRemove->data < (*ptrToRoot)->data) { // Go Left
          if((*ptrToRoot)->leftChild != NULL)
            balanceBefore = (*ptrToRoot)->leftChild->balance;
          nodeToRemove = avlRemove(&(*ptrToRoot)->leftChild, nodeToRemove);
          if((*ptrToRoot)->leftChild != NULL) {
            if(balanceBefore - (*ptrToRoot)->leftChild->balance != 0 && (*ptrToRoot)->leftChild->balance == 0) // did the depth of leftChild changed?
              (*ptrToRoot)->balance++;
          } else {
            if(nodeToRemove != NULL) {
              (*ptrToRoot)->balance++;
            }
          }
          
      } else if(nodeToRemove->data > (*ptrToRoot)->data) { // Go Right
          if((*ptrToRoot)->rightChild != NULL)
            balanceBefore = (*ptrToRoot)->rightChild->balance;
          nodeToRemove = avlRemove(&(*ptrToRoot)->rightChild, nodeToRemove);
          if((*ptrToRoot)->rightChild != NULL) {
            if(balanceBefore - (*ptrToRoot)->rightChild->balance != 0 && (*ptrToRoot)->rightChild->balance == 0) // did the depth of rightChild changed?
              (*ptrToRoot)->balance--;
          } else {
            if(nodeToRemove != NULL) {
              (*ptrToRoot)->balance--;
            }
          }
      }
    }
		
	}
	
  if(nodeToRemove != NULL) {
    nodeToRemove->leftChild = NULL;
    nodeToRemove->rightChild = NULL;
    nodeToRemove->balance = 0;
  }
  
  	// Rotation
  if((*ptrToRoot) != NULL) {
    if((*ptrToRoot)->balance == 2) {
        printf("it rotate left\n");
      if((*ptrToRoot)->rightChild->balance >= 0 ) {
        (*ptrToRoot) = leftRotate((*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleLeftRotate((*ptrToRoot));
      }
      
    } else if((*ptrToRoot)->balance == -2) {
        printf("it rotate right\n");
      if((*ptrToRoot)->leftChild->balance <= 0 ) {
        (*ptrToRoot) = rightRotate((*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleRightRotate((*ptrToRoot));
      }
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
