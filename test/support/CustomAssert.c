#include <stdio.h>
#include "unity.h"
#include "CustomAssert.h"
#include "AVL.h"

void assertAvlNode(	const Node* expectedLeftChild,
					const Node* expectedRightChild,
					const int balanceFactor,
					const Node* actualNode,
					const UNITY_LINE_TYPE lineNumber) {
	if(actualNode == NULL)
		UNITY_TEST_FAIL(lineNumber, "The 'actual' node is NULL");
	UNITY_TEST_ASSERT_EQUAL_PTR(expectedLeftChild, actualNode->leftChild, lineNumber, "The leftChild not the same.");
	UNITY_TEST_ASSERT_EQUAL_PTR(expectedRightChild, actualNode->rightChild, lineNumber, "The RightChild not the same.");
	UNITY_TEST_ASSERT_EQUAL_PTR(balanceFactor, actualNode->balance, lineNumber, "The balance factor not the same.");
}