#include "Rotation.h"
#include "AVL.h"
#include "AVLInt.h"
#include <stdio.h>

/*
 * This function add a node into a BST (Balanced Search Tree)
 * 
 * input:
 *  *root       root node of the BST that adding in new node
 *  *nodeToAdd  new node to be added into the BST
 * return:
 *  *root       root node of the new BST
 */
Node *avlAdd(Node *root, Node *nodeToAdd, int (*compare)(void *, void *)) {
  int compareResult, balanceBefore;
  
  if(nodeToAdd == NULL) {
    return root;
  }
  
	if(root == NULL) { // Reach NULL
		root = nodeToAdd;
		root->balance = 0;
	} else { // Comparison
    
    compareResult = compare(root, nodeToAdd);
    
    if(compareResult == 0) { // Equal
			printf("error\n"); // Throw exception
    
		// else if(nodeToAdd->data < root->data) {
    }  else if(compareResult == 1) { // Go to Left

			if(root->leftChild == NULL) { // leftChild is empty
				root->leftChild = avlAdd(root->leftChild, nodeToAdd, compare);
				root->balance--;
			} else { // leftChild is not empty
				balanceBefore = root->leftChild->balance;
				root->leftChild = avlAdd(root->leftChild, nodeToAdd, compare);
				if(root->leftChild->balance - balanceBefore != 0 && root->leftChild->balance != 0) // Does the depth of left sub tree change?
					root->balance--;
			}
			
		// else if(nodeToAdd->data > root->data) {
    } else if(compareResult == -1) { // Go to Right

			if(root->rightChild == NULL) { // rightChild is empty
				root->rightChild = avlAdd(root->rightChild, nodeToAdd, compare);
				root->balance++;
			} else { // rightChild is not empty
				balanceBefore = root->rightChild->balance;
				root->rightChild = avlAdd(root->rightChild, nodeToAdd, compare);
				if(root->rightChild->balance - balanceBefore != 0 && root->rightChild->balance != 0) // Does the depth of right sub tree change?
					root->balance++;
			}
      
		}
    
	}
	
	// Decide if should do rotation
	if(root->balance == 2) {
		if(root->rightChild->balance >= 0 ) {
			root = leftRotate((Node *)root);
		} else {
			root = doubleLeftRotate((Node *)root);
		}
		
	} else if(root->balance == -2) {
		if(root->leftChild->balance <= 0 ) {
			root = rightRotate((Node *)root);
		} else {
			root = doubleRightRotate((Node *)root);
		}
	}

	return root;
}

/*
 * This function remove a node from a BST (Balanced Search Tree)
 * 
 * input:
 *  **ptrToRoot   pointer to the root node of BST that is removing a node
 *  *nodeToRemove node to be removed from the BST
 * return:
 *  NULL          nodeToRemove cannot be found in the BST
 *  nodeToRemove  node that has been removed successfully from the BST
 */
Node *avlRemove(Node **ptrToRoot, Node *nodeToRemove, int (*compare)(void *, void *)) {
  int compareResult, balanceBefore;
  Node *replacer;
  
	if(nodeToRemove == NULL) { // Removing a NULL
		return NULL;
	} else {
    
    if(*ptrToRoot == NULL) {
      return NULL; // nodeToRemove cannot be found in the tree
      
    } else { // *ptrToRoot is not NULL
    
      compareResult = compare((*ptrToRoot), nodeToRemove);
      
      //if(nodeToRemove->data == (*ptrToRoot)->data) {
      if(compareResult == 0) { // Found nodeToRemove
      
        if((*ptrToRoot)->leftChild != NULL) { // 1st priority on leftChild
          
          balanceBefore = (*ptrToRoot)->leftChild->balance;
          replacer = avlGetReplacer(&(*ptrToRoot)->leftChild); // get re-placer
          replacer->leftChild = (*ptrToRoot)->leftChild;
          replacer->rightChild = (*ptrToRoot)->rightChild;
          replacer->balance = (*ptrToRoot)->balance;
          *ptrToRoot = replacer;

          if((*ptrToRoot)->leftChild == NULL) // do re-placer has a leftChild?
            (*ptrToRoot)->balance++;

          if((*ptrToRoot)->leftChild != NULL) {
            if(balanceBefore != 0 && (*ptrToRoot)->leftChild->balance == 0) // Does the depth of left sub tree change?
              (*ptrToRoot)->balance++;
          } 
            
        } else if((*ptrToRoot)->rightChild != NULL) { // 2nd priority on rightChild
          *ptrToRoot = (*ptrToRoot)->rightChild;
          
        } else {
          *ptrToRoot = NULL; // no leftChild and rightChild
          
        }
        
      // else if(nodeToRemove->data < (*ptrToRoot)->data) {
      } else if(compareResult == 1) { // Go Left
          if((*ptrToRoot)->leftChild != NULL)
            balanceBefore = (*ptrToRoot)->leftChild->balance;
          nodeToRemove = avlRemove(&(*ptrToRoot)->leftChild, nodeToRemove, compare);
          if((*ptrToRoot)->leftChild != NULL) {
            if(balanceBefore != 0 && (*ptrToRoot)->leftChild->balance == 0) // Does the depth of left sub tree change?
              (*ptrToRoot)->balance++;
          } else {
            if(nodeToRemove != NULL) {
              (*ptrToRoot)->balance++;
            }
          }
          
      } else if(compareResult == -1) { // Go Right
          if((*ptrToRoot)->rightChild != NULL)
            balanceBefore = (*ptrToRoot)->rightChild->balance;
          nodeToRemove = avlRemove(&(*ptrToRoot)->rightChild, nodeToRemove, compare);
          if((*ptrToRoot)->rightChild != NULL) {
            if(balanceBefore != 0 && (*ptrToRoot)->rightChild->balance == 0) // Does the depth of right sub tree change?
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
  
  	// Decide if should do rotation
  if((*ptrToRoot) != NULL) {
    if((*ptrToRoot)->balance == 2) {
      if((*ptrToRoot)->rightChild->balance >= 0 ) {
        (*ptrToRoot) = leftRotate((Node *)(*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleLeftRotate((Node *)(*ptrToRoot));
      }
      
    } else if((*ptrToRoot)->balance == -2) {
      if((*ptrToRoot)->leftChild->balance <= 0 ) {
        (*ptrToRoot) = rightRotate((Node *)(*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleRightRotate((Node *)(*ptrToRoot));
      }
    }
  }
  
	return nodeToRemove;
}

/*
 * This function helps avlRemove to find a node that is suitable to replace the removing node in the BST (Balanced Search Tree)
 * 
 * input:
 *  **ptrToRoot   leftChild of the removing node
 * return:
 *  *replacer     replacer node that is suitable to replace the removing node in the BST
 */
Node *avlGetReplacer(Node **ptrToRoot) {
	Node *replacer;
	int balanceBefore;
  
	if((*ptrToRoot)->rightChild != NULL) { // Keep on going
    balanceBefore = (*ptrToRoot)->rightChild->balance;
    
		replacer = avlGetReplacer(&(*ptrToRoot)->rightChild);
    
		if((*ptrToRoot)->rightChild == NULL) { // rightChild is gone after recursion
      (*ptrToRoot)->balance--;
    } else { // rightChild remains after recursion
      if(balanceBefore != 0 && (*ptrToRoot)->rightChild->balance == 0) // Does the depth of right sub tree change?
        (*ptrToRoot)->balance--;
    }
    
	} else { // Replacer is found
		replacer = *ptrToRoot;
    
		if((*ptrToRoot)->leftChild != NULL) { // Replacer has a leftChild
			*ptrToRoot = (*ptrToRoot)->leftChild;
		} else {
			*ptrToRoot = NULL;
    }
  }
  
  replacer->leftChild = NULL;
  replacer->rightChild = NULL;
  replacer->balance = 0;

	// Decide if should do rotation
  if((*ptrToRoot) != NULL) {
    if((*ptrToRoot)->balance == 2) {
      if((*ptrToRoot)->rightChild->balance >= 0 ) {
        (*ptrToRoot) = leftRotate((Node *)(*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleLeftRotate((Node *)(*ptrToRoot));
      }
      
    } else if((*ptrToRoot)->balance == -2) {
      if((*ptrToRoot)->leftChild->balance <= 0 ) {
        (*ptrToRoot) = rightRotate((Node *)(*ptrToRoot));
      } else {
        (*ptrToRoot) = doubleRightRotate((Node *)(*ptrToRoot));
      }
    }
  }
  
	return replacer;
}
