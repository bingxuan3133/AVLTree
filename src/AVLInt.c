#include "AVLInt.h"

int compareInt(void *nodeInTree, void *nodeToCompare) {
  NodeInt *node1 = (NodeInt *)nodeInTree;
  NodeInt *node2 = (NodeInt *)nodeToCompare;
  
  if(node1->data == node2->data) return 0;
  else if(node1->data > node2->data) return 1;
  else if(node1->data < node2->data) return -1;
}
