#ifndef AVL_H
#define AVL_H

typedef struct Node Node;

struct Node {
	int balance;
	Node *leftChild;
	Node *rightChild;
	int data;
};

Node *avlAdd(Node *root, Node *noteToAdd);

#endif // AVL_H
