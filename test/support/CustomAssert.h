#ifndef CustomAssert_H
#define CustomAssert_H

#define TEST_ASSERT_EQUAL_AVL_NODE(expectedLeftChild, expectedRightChild, balanceFactor, actualNode) \
					assertAvlNode(expectedLeftChild, expectedRightChild, balanceFactor, actualNode, __LINE__)

#endif // CustomAssert_H
