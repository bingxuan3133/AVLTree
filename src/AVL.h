#ifndef AVL_H
#define AVL_H

typedef struct Node Node;

struct Node {
	int balance;
	Node *leftChild;
	Node *rightChild;
};

Node *avlAdd(Node *root, Node *noteToAdd, int (*compare)(void *, void *));
Node *avlRemove(Node **ptrToRoot, Node *nodeToRemove, int (*compare)(void *, void *));
Node *avlGetReplacer(Node **ptrToRoot);

#endif // AVL_H
