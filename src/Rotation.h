#ifndef Rotation_H
#define Rotation_H

#include "AVL.h"

int getHeight(Node *elem);
Node *rightRotate(Node *parent);
Node *leftRotate(Node *parent);
Node *doubleRightRotate(Node *parent);
Node *doubleLeftRotate(Node *parent);

#endif // Rotation_H
