#include "AVLString.h"

int compareString(void *nodeInTree, void *nodeToCompare) {
  Node *node1 = (Node *)nodeInTree;
  Node *node2 = (Node *)nodeToCompare;
  
  if(node1->data == node2->data) return 0;
  else if(node1->data > node2->data) return 1;
  else if(node1->data < node2->data) return -1;
}
