#ifndef AVL_H
#define AVL_H

typedef struct Node Node;

struct Node {
	int rank;
	Node *leftChild;
	Node *rightChild;
	int data;
};

#endif // AVL_H
