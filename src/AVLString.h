#ifndef AVLString_H
#define AVLString_H

#include "AVL.h"

#define avlAddString(root, nodeToAdd) avlAdd(root, nodeToAdd, compareString)

typedef struct NodeString NodeString;

struct NodeString {
	int balance;
	NodeString *leftChild;
	NodeString *rightChild;
	char* string;
};

int compareString(void *nodeInTree, void *nodeToCompare);

#endif // AVLString_H