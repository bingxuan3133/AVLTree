#ifndef AVL_H
#define AVL_H

typedef struct Node Node;

struct Node {
	int balance;
	Node *leftChild;
	Node *rightChild;
	int data;
};

#endif // AVL_H
