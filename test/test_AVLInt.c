#include "unity.h"
#include "Rotation.h"
#include "getHeight.h"
#include "AVL.h"
#include "AVLInt.h"
#include "CustomAssert.h"

void setUp(void)
{
}

void tearDown(void)
{
}


/////////////////////////////////////////////////
// Test avlAddInt
/////////////////////////////////////////////////

/*
 *		  100 (1)
 *	   /   \
 *	 50		150 (-1 -> 0)
 *		   /   \
 *		120   *200
 *
 *	*nodeToAdd
 */
void test_avlAddInt_focus_on_balance_factor_while_tree_height_remains_case_1() {
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=-1, .leftChild=&node120, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=&node50, .rightChild=&node150};
	
	NodeInt *root = &node100;
	
	root = avlAddInt(root, &node200);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&node100, root);
	TEST_ASSERT_EQUAL_PTR(&node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node120, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node200, root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node200.balance);
	TEST_ASSERT_EQUAL(0, node120.balance);
	TEST_ASSERT_EQUAL(0, node150.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(1, node100.balance);
}

/*
 *		  100 (1)
 *	   /   \
 *	 50		 150 (1 -> 0)
 *		    /  \
 *		*120	 200
 *
 *	*nodeToAdd
 */
void test_avlAddInt_focus_on_balance_factor_while_tree_height_remains_case_2() {
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=&node50, .rightChild=&node150};
	
	NodeInt *root = &node100;
	
	root = avlAddInt(root, &node120);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&node100, root);
	TEST_ASSERT_EQUAL_PTR(&node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node120, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node200, root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node200.balance);
	TEST_ASSERT_EQUAL(0, node120.balance);
	TEST_ASSERT_EQUAL(0, node150.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(1, node100.balance);
}

/*
 *		1 (0 -> 1)
 *		 \
 *		 *50
 *
 *	*nodeToAdd
 */
void test_avlAddInt_focus_on_balance_factor_while_tree_height_changes_case_1() {
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	
	NodeInt *root = &node1;
	
	root = avlAddInt(root, &node50);
	
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node50, 1, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
}

/*
 *		  100 (0 -> 1)
 *	   /   \
 *	  50	 150 (0 -> -1)
 *		     /
 *  		*120
 *
 *	*nodeToAdd
 */
void test_avlAddInt_focus_on_balance_factor_while_tree_height_changes_case_2() {
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=&node50, .rightChild=&node150};
	
	NodeInt *root = &node100;
	
	root = avlAddInt(root, &node120);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node150, 1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(&node120, NULL, -1, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node120);
}

/*
 *		  100 (0 -> 1)
 *	   /  \
 *	  50	150 (0 -> 1)
 *			    \
 *				  *200
 *
 *	*nodeToAdd
 */
void test_avlAddInt_focus_on_balance_factor_while_tree_height_changes_case_3() {
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=&node50, .rightChild=&node150};
	
	NodeInt *root = &node100;
	
	root = avlAddInt(root, &node200);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node150, 1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node200, 1, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *		1
 */
void test_avlAddInt_1() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&node1, root);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	
	TEST_ASSERT_EQUAL(0, node1.balance);
}

/*
 *		1
 *		 \
 *		 50	
 */
void test_avlAddInt_1_50() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&node1, root);
	TEST_ASSERT_EQUAL_PTR(&node50, root->rightChild);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node50.leftChild);
	TEST_ASSERT_NULL(node50.rightChild);
	
	TEST_ASSERT_EQUAL(1, node1.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
}

/*
 *		1
 *		 \					50
 *		 50		=>	 /  \
 *		  \				1	  100
 *			100
 */
void test_avlAddInt_1_50_100() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node100, root->rightChild);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node100.leftChild);
	TEST_ASSERT_NULL(node100.rightChild);
	
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(0, node100.balance);
}

/*
 *		  50
 *	 	 /	\
 *		1	  100
 *			  /
 *		  75
 */
void test_avlAddInt_1_50_100_75() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node100, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node75, root->rightChild->leftChild);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node100.rightChild);
	TEST_ASSERT_NULL(node75.leftChild);
	TEST_ASSERT_NULL(node75.rightChild);
	
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(1, node50.balance);
	TEST_ASSERT_EQUAL(-1, node100.balance);
	TEST_ASSERT_EQUAL(0, node75.balance);
}

/*
 *		  50
 *	 	 /	\
 *		1	  100
 *			  / \
 *		  75  150
 */
void test_avlAddInt_1_50_100_75_150() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	root = avlAddInt(root, &node150);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node100, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node75, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node150, root->rightChild->rightChild);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node75.leftChild);
	TEST_ASSERT_NULL(node75.rightChild);
	TEST_ASSERT_NULL(node150.leftChild);
	TEST_ASSERT_NULL(node150.rightChild);
	
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(1, node50.balance);
	TEST_ASSERT_EQUAL(0, node100.balance);
	TEST_ASSERT_EQUAL(0, node75.balance);
	TEST_ASSERT_EQUAL(0, node150.balance);
}

/*
 *		  50				    100
 *	 	 /	\			    	/	\
 *		1	100			    50	150
 *			/ \		=>	 /  \	  \
 *		75  150		  1	  75  200
 *				 \
 *			  200
 */
void test_avlAddInt_1_50_100_75_150_200() {
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	root = avlAddInt(root, &node150);
	root = avlAddInt(root, &node200);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node150, 0, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node75, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node200, 1, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *		  50				     100
 *	 	 / \				    /	 \
 *		1	 100			  50	 150
 *			/ \	  =>	 / \	 /  \
 *		75  150		  1  75 120 200
 *				\
 *				200
 */
void test_avlAddInt_1_50_100_75_150_200_120() {
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	root = avlAddInt(root, &node150);
	root = avlAddInt(root, &node200);
	root = avlAddInt(root, &node120);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node150, 0, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node75, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node120, &node200, 0, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node120);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *			   100
 *			  /	  \
 *		  50		 150
 *		 / \		/	\
 *		1  75 120 200
 *			  	/
 *			  110
 */
void test_avlAddInt_1_50_100_75_150_200_120_110() {
	NodeInt node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	root = avlAddInt(root, &node150);
	root = avlAddInt(root, &node200);
	root = avlAddInt(root, &node120);
	root = avlAddInt(root, &node110);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node150, 1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node75, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node120, &node200, -1, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
	TEST_ASSERT_EQUAL_AVL_Node(&node110, NULL, -1, &node120);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node110);
}

/*
 *			   100
 *			  /	  \
 *		  50		150
 *		 / \		/	\
 *		1  75 120  200
 *			  	/	    \
 *			  110	    130
 */
void test_avlAddInt_1_50_100_75_150_200_120_110_130() {
	NodeInt node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	root = avlAddInt(root, &node150);
	root = avlAddInt(root, &node200);
	root = avlAddInt(root, &node120);
	root = avlAddInt(root, &node110);
	root = avlAddInt(root, &node130);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node150, 1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node75, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node120, &node200, -1, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
	TEST_ASSERT_EQUAL_AVL_Node(&node110, &node130, 0, &node120);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node110);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node130);
}

/*
 *			   100
 *			  /	  \
 *		  50		 150
 *		 / \		/	  \
 *		1  75 120   200
 *			  	/	\	    \
 *			  110 130	  250
 */
void test_avlAddInt_1_50_100_75_150_200_120_110_130_250() {
	NodeInt node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	root = avlAddInt(root, &node150);
	root = avlAddInt(root, &node200);
	root = avlAddInt(root, &node120);
	root = avlAddInt(root, &node110);
	root = avlAddInt(root, &node130);
	root = avlAddInt(root, &node250);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node150, 1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node75, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node120, &node200, 0, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
	TEST_ASSERT_EQUAL_AVL_Node(&node110, &node130, 0, &node120);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node250, 1, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node110);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node130);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node250);
}

/*
 *			   100                        120
 *			  /   \                      /   \
 *		  50		 150                100    150
 *		 / \		 /	\              /  \    /  \
 *		1  75  120  200     =>    50 110 130  200
 *			  	 /	\	  \          / \      \     \
 *			   110  130	250       1   75    140   250
 *					 \
 *					 140
 */
void test_avlAddInt_1_50_100_75_150_200_120_110_130_250_140() {
	NodeInt node140 = {.data=140, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = NULL;
	
	root = avlAddInt(root, &node1);
	root = avlAddInt(root, &node50);
	root = avlAddInt(root, &node100);
	root = avlAddInt(root, &node75);
	root = avlAddInt(root, &node150);
	root = avlAddInt(root, &node200);
	root = avlAddInt(root, &node120);
	root = avlAddInt(root, &node110);
	root = avlAddInt(root, &node130);
	root = avlAddInt(root, &node250);
	root = avlAddInt(root, &node140);
	
	TEST_ASSERT_EQUAL_AVL_Node(&node100, &node150, 0, &node120);
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node110, -1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(&node130, &node200, 0, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node75, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node110);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node140, 1, &node130);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node250, 1, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node140);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node250);
}


/////////////////////////////////////////////////
// Test avlGetReplacer
/////////////////////////////////////////////////

// My own test cases

/*
 *		1 (Replacing NodeInt)
 */
void test_avlGetReplacer_case_1() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	
	NodeInt *root = &node1;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
}

/*
 *			50 (Replacing NodeInt)
 *		 /
 *		1
 */
void test_avlGetReplacer_case_2() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	
	NodeInt *root = &node50;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node1, root);
	TEST_ASSERT_EQUAL_PTR(&node50, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
}

/*
 *		1
 *		 \
 *			50 (Replacing NodeInt)
 */
void test_avlGetReplacer_case_3() {
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&node50};
	
	NodeInt *root = &node1;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node1, root);
	TEST_ASSERT_EQUAL_PTR(&node50, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
}

/*
 *			50
 *     /  \
 *		1		100 (Replacing NodeInt)
 */
void test_avlGetReplacer_case_4() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node1, .rightChild=&node100};
	
	NodeInt *root = &node50;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node100, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node100);
}

/*
 *			50
 *     /  \
 *		1		100 (Replacing NodeInt)
 *        /
 *      75
 */
void test_avlGetReplacer_case_5() {
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node75, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=1, .leftChild=&node1, .rightChild=&node100};
	
	NodeInt *root = &node50;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node100, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node75, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node100);
}

/*
 *			50
 *     /  \
 *		10	100
 *   /    / \
 *  1   75  200 (Replacing NodeInt)
 *          /
 *        150
 */
void test_avlGetReplacer_case_6() {
  NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node200 = {.data=200, .balance=-1, .leftChild=&node150, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=&node75, .rightChild=&node200};
  NodeInt node10 = {.data=10, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=1, .leftChild=&node10, .rightChild=&node100};
	
	NodeInt *root = &node50;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node200, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node10, &node100, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node10);
	TEST_ASSERT_EQUAL_AVL_Node(&node75, &node150, 0, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
 	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *			 50                                  30
 *      /  \                                /  \
 *		10	 100                            10    50
 *   / \    \                       =>   / \   / \
 *  1  30   200 (Replacing NodeInt)        1  20 40 100
 *    / \ 
 *   20 40 
 */
void test_avlGetReplacer_case_7() {
  NodeInt node20 = {.data=20, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node30 = {.data=30, .balance=0, .leftChild=&node20, .rightChild=&node40};
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node10 = {.data=10, .balance=1, .leftChild=&node1, .rightChild=&node30};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node10, .rightChild=&node100};
	
	NodeInt *root = &node50;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node30, root);
	TEST_ASSERT_EQUAL_PTR(&node200, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node10, &node50, 0, &node30);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node20, 0, &node10);
	TEST_ASSERT_EQUAL_AVL_Node(&node40, &node100, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node20);
 	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *			 50                           10
 *      /  \                         /  \
 *		10	 100 (Replacing NodeInt) =>  1   50
 *   /
 *  1
 */
void test_avlGetReplacer_case_8() {
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node10 = {.data=10, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node10, .rightChild=&node100};
	
	NodeInt *root = &node50;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node10, root);
	TEST_ASSERT_EQUAL_PTR(&node100, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node50, 0, &node10);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node100);
}


// Email requirements test cases
/*
 *      50             50
 *     /  \     =>    /  \
 *   25   200       25   200
 *        / \            /
 *      150 220        150
 * 
 * where 220 is being removed
 */
void test_avlGetReplacer_case_5b() {
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=&node150, .rightChild=&node220};
	NodeInt node50 = {.data=50, .balance=1, .leftChild=&node25, .rightChild=&node200};
	
	NodeInt *root = &node50;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node220, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node200, 1, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(&node150, NULL, -1, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        100                  100                50
 *      /    \               /    \             /    \
 *     25    150           25     150         25     100
 *    /  \     \    =>    /  \          =>   /  \    /  \
 *   1   50    200       1   50             1   40  75  150
 *      /  \                /  \
 *     40  75              40  75
 *
 * where 200 is being removed
 */
void test_avlGetReplacer_case_9() {
  NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node50 = {.data=50, .balance=0, .leftChild=&node40, .rightChild=&node75};
  NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
  NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	
	NodeInt *root = &node100;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node200, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(&node1, &node40, 0, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(&node75, &node150, 0, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        100                  100                50
 *      /    \               /    \             /    \
 *     25    150           25     150         25     100
 *    /  \     \    =>    /  \          =>   /       /  \
 *   1   50    200       1   50             1      75  150
 *         \                   \
 *         75                  75
 *
 * where 200 is being removed
 */
void test_avlGetReplacer_case_10() {
  NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node50 = {.data=50, .balance=1, .leftChild=NULL, .rightChild=&node75};
  NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
  NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	
	NodeInt *root = &node100;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node200, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(&node75, &node150, 0, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        100                  100                50
 *      /    \               /    \             /    \
 *     25    150           25     150         25     100
 *    /  \     \    =>    /  \          =>   /  \       \
 *   1   50    200       1   50             1   40      150
 *      /                   /
 *     40                  40
 *
 * where 200 is being removed
 */
void test_avlGetReplacer_case_11() {
  NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node40, .rightChild=NULL};
  NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
  NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	
	NodeInt *root = &node100;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node200, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(&node1, &node40, 0, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node150, 1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        100                  100                40
 *      /    \               /    \             /    \
 *     40    150           40     150         25     100
 *    /  \     \    =>    /  \          =>   /       /  \
 *   25  75   200        25  75             1      75   150
 *  /    /              /    /                    /
 * 1    50             1    50                  50
 *
 * where 200 is being removed
 */
void test_avlGetReplacer_case_12() {
  NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
  NodeInt node75 = {.data=75, .balance=-1, .leftChild=&node50, .rightChild=NULL};
  NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node40 = {.data=40, .balance=0, .leftChild=&node25, .rightChild=&node75};
  NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node40, .rightChild=&node150};
	
	NodeInt *root = &node100;
	NodeInt *replacernode;
	
	replacernode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacernode);
	TEST_ASSERT_EQUAL_PTR(&node40, root);
	TEST_ASSERT_EQUAL_PTR(&node200, replacernode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 1, &node40);
  TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(&node75, &node150, -1, &node100);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(&node50, NULL, -1, &node75);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
}


/////////////////////////////////////////////////
// Test avlRemoveInt
/////////////////////////////////////////////////

// My own test cases

/*
 *    1 (NodeInt to remove)
 */
void test_avlRemove_node1_from_1_element_AVL_tree() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = &node1;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node1);
	
	TEST_ASSERT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL_PTR(&node1, removedNode);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
}

/*
 *    1 (NodeInt to remove)
 *     \
 *     50
 */
void test_avlRemove_node1_from_2_elements_AVL_tree() {
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&node50};
	
	NodeInt *root = &node1;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node1);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node1, removedNode);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
}

/*
 *    1
 *     \
 *     50 (NodeInt to remove)
 */
void test_avlRemove_node50_from_2_elements_AVL_tree() {
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&node50};
	
	NodeInt *root = &node1;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node50);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node1, root);
  TEST_ASSERT_EQUAL_PTR(&node50, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
}


// Email requirements test cases

////////////////////////////////////////////////////////////
// Test avlRemoveInt() on deletion of NodeInt on the left subtree
////////////////////////////////////////////////////////////

/*
 *      50  => NULL
 *
 * where 50 is being removed 
 */
void test_avlRemove_for_left_subtree_case_1() {
	NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = &node50;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node50);
	
	TEST_ASSERT_NULL(root);
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL_PTR(&node50, removedNode);
}
 
/*
 *        50                 50
 *       /  \               /  \
 *     25   150    =>     25   150
 *             \                  \
 *             200                200
 *
 * Attempt to remove 1, which cannot be found in the tree.
 */
void test_avlRemove_for_left_subtree_case_2() {
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node50 = {.data=50, .balance=1, .leftChild=&node25, .rightChild=&node150};
  NodeInt node1= {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = &node50;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node1);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NULL(removedNode); // node1 cannot be found in the tree
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node150, 1, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node200, 1, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
}

/*
 *      50             50
 *     /  \     =>       \
 *   25   150            150
 *
 * where 25 is being removed
 */
void test_avlRemove_for_left_subtree_case_3() {
	NodeInt node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node50;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node25);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node150, 1, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        50                 150
 *      /   \               /  \
 *     25   150    =>     50   200
 *             \
 *             200
 *
 * where 25 is being removed
 */
void test_avlRemove_for_left_subtree_case_4() {
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node50 = {.data=50, .balance=1, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node50;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node25);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node150, root);
  TEST_ASSERT_EQUAL_PTR(&node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node50, &node200, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
}

/*
 *        50                 50
 *      /   \               /  \
 *    25    150    =>     1    150
 *    /       \                  \
 *   1       200                 200
 *
 * where 25 is being removed
 */
void test_avlRemove_for_left_subtree_case_5() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node50;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node25);
  
  // printf("=== THIS TEST ===\n"); 
  // printf("root:%d\n", root->data);
  // printf("root->leftChild:%d\n", root->leftChild->data);
  // printf("root->rightChild:%d\n", root->rightChild->data);
  // if(root->leftChild->leftChild != NULL)
    // printf("root->leftChild->leftChild:%d\n", root->leftChild->leftChild->data);
  // if(root->leftChild->rightChild != NULL)
    // printf("root->leftChild->rightChild:%d\n", root->leftChild->rightChild->data);
  // if(root->rightChild->leftChild != NULL)
    // printf("root->rightChild->leftChild:%d\n", root->rightChild->leftChild->data);	
  // if(root->rightChild->rightChild != NULL)
    // printf("root->rightChild->rightChild:%d\n", root->rightChild->rightChild->data);
  
  // printf("show node1 balance:%d\n", node1.balance);
  // printf("=== END ===\n");
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node150, 1, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node200, 1, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
}

/*
 *        100                  100                    150
 *      /    \               /    \                 /    \
 *    25     200           25     200             100     200
 *    /     /  \    =>            /  \     =>    /  \     /  \
 *   1    150  220              150  220        25  120 175  220
 *       /  \                  /  \
 *     120  175              120  175
 *
 * where 1 is being removed
 */
void test_avlRemove_for_left_subtree_case_6() {
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node175 = {.data=175, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=&node120, .rightChild=&node175};
	NodeInt node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=-1, .leftChild=&node150, .rightChild=&node220};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node100;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node150, root);
  TEST_ASSERT_EQUAL_PTR(&node1, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node100, &node200, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, &node120, 0, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(&node175, &node220, 0, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node120);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node175);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node220);
}

/*
 *        100                  100                    150
 *      /    \               /    \                 /    \
 *    25     200           25     200             100     200
 *    /     /  \    =>            /  \     =>    /  \       \
 *   1    150  220              150  220        25  120     220
 *       /                     /
 *     120                   120
 *
 * where 1 is being removed
 */
void test_avlRemove_for_left_subtree_case_7() {
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=-1, .leftChild=&node120, .rightChild=NULL};
	NodeInt node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=-1, .leftChild=&node150, .rightChild=&node220};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node100;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node150, root);
  TEST_ASSERT_EQUAL_PTR(&node1, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node100, &node200, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, &node120, 0, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node220, 1, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node120);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node220);
}

/*
 *        100                  100                    150
 *      /    \               /    \                 /    \
 *    25     200           25     200             100     200
 *    /     /  \    =>            /  \     =>    /        /  \
 *   1    150  220              150  220        25      175  220
 *          \                     \
 *          175                   175
 *
 * where 1 is being removed
 */
void test_avlRemove_for_left_subtree_case_8() {
	NodeInt node175 = {.data=175, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node175};
	NodeInt node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=-1, .leftChild=&node150, .rightChild=&node220};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node100;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node150, root);
  TEST_ASSERT_EQUAL_PTR(&node1, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node100, &node200, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, NULL, -1, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(&node175, &node220, 0, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node175);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node220);
}

/*
 *        100                  100                    200
 *      /    \               /    \                 /    \
 *    25     200           25     200             100     220
 *    /     /  \    =>            /  \     =>    /  \       \
 *   1    150  220              150  220        25  150     250
 *          \    \                \    \              \
 *          175  250              175  250            175
 *
 * where 1 is being removed
 */
void test_avlRemove_for_left_subtree_case_9() {
	NodeInt node175 = {.data=175, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node175};
	NodeInt node220 = {.data=220, .balance=1, .leftChild=NULL, .rightChild=&node250};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=&node150, .rightChild=&node220};
	NodeInt node100 = {.data=100, .balance=1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node100;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node200, root);
  TEST_ASSERT_EQUAL_PTR(&node1, removedNode);
  TEST_ASSERT_EQUAL_AVL_Node(&node100, &node220, -1, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, &node150, 1, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node250, 1, &node220);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, &node175, 1, &node150);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node175);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node250);
}
 
/*
 *      50             50
 *     /  \     =>    /  \
 *   25   200       40   200
 *    \
 *    40
 *
 * where 25 is being removed
 */
void test_avlRemove_for_left_subtree_case_10() {
	NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=1, .leftChild=NULL, .rightChild=&node40};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node50;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node25);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node40, &node200, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
}
 
/*
 *       50             50
 *      /  \     =>    /  \
 *    25   200        1   200
 *   / \               \
 *  1  40              40
 *
 * where 25 is being removed
 */
void test_avlRemove_for_left_subtree_case_11() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=0, .leftChild=&node1, .rightChild=&node40};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node50;
	NodeInt *removedNode;
	
	removedNode = avlRemoveInt(&root, &node25);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node200, -1, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node40, 1, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
}
 
/*
 *      150              90
 *     /  \             /  \
 *   25   200    =>   25   200
 *  / \     \        / \     \
 * 1   50   250     1   50   250
 *       \
 *       90
 *
 * where 150 is being removed
 */
void test_avlRemove_for_left_subtree_case_12() {
	NodeInt node90 = {.data=90, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=1, .leftChild=NULL, .rightChild=&node90};
	NodeInt node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
	NodeInt node200 = {.data=200, .balance=1, .leftChild=NULL, .rightChild=&node250};
	NodeInt node150 = {.data=150, .balance=-1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node150;
	NodeInt *removedNode;

  removedNode = avlRemoveInt(&root, &node150);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node90, root);
  TEST_ASSERT_EQUAL_PTR(&node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node200, 0, &node90);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node50, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node250, 1, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node250);
}
 
/*
 *      150              90
 *     /  \             /  \
 *   25   200    =>   25   200
 *  / \     \        / \     \
 * 1   50   250     1   50   250
 *    /  \              /
 *   40  90            40
 *
 * where 150 is being removed
 */
void test_avlRemove_for_left_subtree_case_13() {
	NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node90 = {.data=90, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node40, .rightChild=&node90};
	NodeInt node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
	NodeInt node200 = {.data=200, .balance=1, .leftChild=NULL, .rightChild=&node250};
	NodeInt node150 = {.data=150, .balance=-1, .leftChild=&node25, .rightChild=&node200};
	NodeInt *root = &node150;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node150);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node90, root);
  TEST_ASSERT_EQUAL_PTR(&node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node200, -1, &node90);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node50, 1, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node250, 1, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(&node40, NULL, -1, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node250);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
}


/////////////////////////////////////////////////////////////
// Test avlRemoveInt() on deletion of NodeInt on the right subtree
/////////////////////////////////////////////////////////////

/*
 *        50                 50
 *      /   \               /  \
 *     25   150    =>     25   150
 *    /                  /
 *   1                  1
 *
 * Attempt to remove 200, which cannot be found in the tree.
 */
void test_avlRemove_for_right_subtree_case_1() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt *root = &node50;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node200);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, &node150, -1, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}
 
/*
 *      50             50
 *     /  \     =>    /
 *   25   150       25
 *
 * where 150 is being removed
 */
void test_avlRemove_for_right_subtree_case_2() {
	NodeInt node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node50;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node150);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node150, removedNode);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, NULL, -1, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}
 
/*
 *        50                 50            25
 *      /   \               /            /   \
 *     25   150    =>     25       =>   1    50
 *    /                  /
 *   1                  1
 *
 * where 150 is being removed
 */
void test_avlRemove_for_right_subtree_case_3() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node50;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node150);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node25, root);
  TEST_ASSERT_EQUAL_PTR(&node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node50, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        50                 50
 *      /   \               /  \
 *     25   150    =>     25   200
 *    /       \          /
 *   1       200        1
 *
 * where 150 is being removed
 */
void test_avlRemove_for_right_subtree_case_4() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node50;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node150);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node200, -1, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        100                  100                50
 *      /    \               /    \             /    \
 *     25    150           25     150         25     100
 *    /  \     \    =>    /  \          =>   /  \    /  \
 *   1   50    200       1   50             1   40  75  150
 *      /  \                /  \
 *     40  75              40  75
 *
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_5() {
	NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node40, .rightChild=&node75};
	NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node100;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node200);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node40, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(&node75, &node150, 0, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        100                  100                50
 *      /    \               /    \             /    \
 *     25    150           25     150         25     100
 *    /  \     \    =>    /  \          =>   /       /  \
 *   1   50    200       1   50             1      75  150
 *         \                   \
 *         75                  75
 *
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_6() {
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=1, .leftChild=NULL, .rightChild=&node75};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node100;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node200);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(&node75, &node150, 0, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node75);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}
 
/*
 *        100                  100                50
 *      /    \               /    \             /    \
 *     25    150           25     150         25     100
 *    /  \     \    =>    /  \          =>   /  \       \
 *   1   50    200       1   50             1   40      150
 *      /                   /
 *     40                  40
 *
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_7() {
	NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-1, .leftChild=&node40, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node25 = {.data=25, .balance=1, .leftChild=&node1, .rightChild=&node50};
	NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node25, .rightChild=&node150};
	NodeInt *root = &node100;
	NodeInt *removedNode;

	removedNode = avlRemoveInt(&root, &node200);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 0, &node50);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, &node40, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node150, 1, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node40);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
}

/*
 *        100                  100                40
 *      /    \               /    \             /    \
 *     40    150           40     150         25     100
 *    /  \     \    =>    /  \          =>   /       /  \
 *   25  75   200        25  75             1      75   150
 *  /    /              /    /                    /
 * 1    50             1    50                  50
 *
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_8() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node25 = {.data=25, .balance=-1, .leftChild=&node1, .rightChild=NULL};
  NodeInt node75 = {.data=75, .balance=-1, .leftChild=&node50, .rightChild=NULL};
  NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  NodeInt node40 = {.data=40, .balance=0, .leftChild=&node25, .rightChild=&node75};
  NodeInt node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node40, .rightChild=&node150};
  NodeInt *root = &node100;
  NodeInt *removedNode;  
  
	removedNode = avlRemoveInt(&root, &node200);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node40, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_Node(&node25, &node100, 1, &node40);
	TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(&node75, &node150, -1, &node100);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(&node50, NULL, -1, &node75);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *      50             50
 *     /  \     =>    /  \
 *   25   200       25   150
 *        /
 *      150
 *
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_9() {
  NodeInt node150 = {.data = 150, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node25 = {.data = 25, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node200 = {.data = 200, .balance = -1, .leftChild = &node150, .rightChild = NULL};
  NodeInt node50 = {.data = 50, .balance = 1, .leftChild = &node25, .rightChild = &node200};
  NodeInt *root = &node50;
	NodeInt *removedNode;
	
  removedNode = avlRemoveInt(&root,&node200);
  
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, &node150, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}
 
/*
 *      50             50
 *     /  \     =>    /  \
 *   25   200       25   150
 *        / \              \
 *      150 220            220
 *
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_10() {
  NodeInt node150 = {.data = 150, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node25 = {.data = 25, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node220 = {.data = 220, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node200 = {.data = 200, .balance = 0, .leftChild = &node150, .rightChild = &node220};
  NodeInt node50 = {.data = 50, .balance = 1, .leftChild = &node25, .rightChild = &node200};
  NodeInt *root = &node50;
	NodeInt *removedNode;
	
  removedNode = avlRemoveInt(&root,&node200);
  
 	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, &node150, 1, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, &node220, 1, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node220);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *      50               50
 *     /  \             /  \
 *   25   200    =>   25   175
 *  /     / \        /    /  \
 * 1    150 250     1   150  250
 *        \
 *        175
 *
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_11() {
  NodeInt node1 = {.data = 1, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node250 = {.data = 250, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node175 = {.data = 175, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node150 = {.data = 150, .balance = 1, .leftChild = NULL, .rightChild = &node175};
  NodeInt node200 = {.data = 200, .balance = -1, .leftChild = &node150, .rightChild = &node250};
  NodeInt node25 = {.data = 25, .balance = -1, .leftChild = &node1, .rightChild = NULL};
  NodeInt node50 = {.data = 50, .balance = 1, .leftChild = &node25, .rightChild = &node200};
  NodeInt *root = &node50;
	NodeInt *removedNode;
	
  removedNode = avlRemoveInt(&root,&node200);
  
 	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);
  TEST_ASSERT_EQUAL_AVL_Node(&node25, &node175, 0, &node50);
  TEST_ASSERT_EQUAL_AVL_Node(&node1, NULL, -1, &node25);
  TEST_ASSERT_EQUAL_AVL_Node(&node150, &node250, 0, &node175);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node250);
  TEST_ASSERT_EQUAL_AVL_Node(NULL, NULL, 0, &node200);
}

/*
 *      50               50
 *     /  \             /  \
 *   25   200    =>   25   175
 *  /     / \        /    /  \
 * 1    150 250     1   150  250
 *      / \             /
 *    120 175         120
 * 
 * where 200 is being removed
 */
void test_avlRemove_for_right_subtree_case_12() {
  NodeInt node1 = {.data = 1, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node250 = {.data = 250, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node175 = {.data = 175, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node120 = {.data = 120, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node150 = {.data = 150, .balance = 0, .leftChild = &node120, .rightChild = &node175};
  NodeInt node200 = {.data = 200, .balance = -1, .leftChild = &node150, .rightChild = &node250};
  NodeInt node25 = {.data = 25, .balance = -1, .leftChild = &node1, .rightChild = NULL};
  NodeInt node50 = {.data = 50, .balance = 1, .leftChild = &node25, .rightChild = &node200};
  NodeInt *root = &node50;
	NodeInt *removedNode;
  
  removedNode = avlRemoveInt(&root,&node200);

  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
  TEST_ASSERT_EQUAL_PTR(&node200, removedNode);  
  TEST_ASSERT_EQUAL_AVL_Node(&node25,&node175,1,&node50);
  TEST_ASSERT_EQUAL_AVL_Node(&node1,NULL,-1,&node25);
  TEST_ASSERT_EQUAL_AVL_Node(&node150,&node250,-1,&node175);
  TEST_ASSERT_EQUAL_AVL_Node(&node120,NULL,-1,&node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node1);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node120);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node250);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node200);
}

/*
 *              175                                   175
 *          /          \                         /          \
 *        100          400                     100          350
 *       /   \       /     \                  /   \       /     \
 *     50    150   250     500       =>     50    150   250     500
 *    / \    /   /    \     / \            / \    /   /    \     / \
 *  25  65 120 200    300 450 550        25  65 120 200    300 450 550
 *   \          \     / \      \          \          \     / \      \
 *   40         220 270 350    600        40         220 270 330    600
 *                      /
 *                    330
 *
 * where 400 is being removed
 */
void test_avlRemove_for_right_subtree_case_13() {
  NodeInt node40 = {.data = 40, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node65 = {.data = 65, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node120 = {.data = 120, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node220 = {.data = 220, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node270 = {.data = 270, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node330 = {.data = 330, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node450 = {.data = 450, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node600 = {.data = 600, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  NodeInt node25 = {.data = 25, .balance = 1, .leftChild = NULL, .rightChild = &node40};
  NodeInt node150 = {.data = 150, .balance = -1, .leftChild = &node120, .rightChild = NULL};
  NodeInt node200 = {.data = 200, .balance = 1, .leftChild = NULL, .rightChild = &node220};
  NodeInt node350 = {.data = 350, .balance = -1, .leftChild = &node330, .rightChild = NULL};
  NodeInt node550 = {.data = 550, .balance = 1, .leftChild = NULL, .rightChild = &node600};
  NodeInt node300 = {.data = 300, .balance = 1, .leftChild = &node270, .rightChild = &node350};
  NodeInt node500 = {.data = 500, .balance = 1, .leftChild = &node450, .rightChild = &node550};
  NodeInt node50 = {.data = 50, .balance = -1, .leftChild = &node25, .rightChild = &node65};
  NodeInt node250 = {.data = 250, .balance = 1, .leftChild = &node200, .rightChild = &node300};
  NodeInt node100 = {.data = 100, .balance = -1, .leftChild = &node50, .rightChild = &node150};
  NodeInt node400 = {.data = 400, .balance = -1, .leftChild = &node250, .rightChild = &node500};
  NodeInt node175 = {.data = 175, .balance = 1, .leftChild = &node100, .rightChild = &node400};
  NodeInt *root = &node175;
	NodeInt *removedNode;
	
  removedNode = avlRemoveInt(&root,&node400);
  
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&node175, root);
  TEST_ASSERT_EQUAL_PTR(&node400, removedNode);  
  
  TEST_ASSERT_EQUAL_AVL_Node(&node100,&node350,0,&node175);
  
  TEST_ASSERT_EQUAL_AVL_Node(&node50,&node150,-1,&node100);
  TEST_ASSERT_EQUAL_AVL_Node(&node250,&node500,0,&node350);
  
  TEST_ASSERT_EQUAL_AVL_Node(&node450,&node550,1,&node500);
  TEST_ASSERT_EQUAL_AVL_Node(&node200,&node300,0,&node250);
  TEST_ASSERT_EQUAL_AVL_Node(&node25,&node65,-1,&node50);
  
  TEST_ASSERT_EQUAL_AVL_Node(NULL,&node600,1,&node550);
  TEST_ASSERT_EQUAL_AVL_Node(&node270,&node330,0,&node300);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,&node220,1,&node200);
  TEST_ASSERT_EQUAL_AVL_Node(&node120,NULL,-1,&node150);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,&node40,1,&node25);
  
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node40);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node65);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node120);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node220);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node270);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node330);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node450);
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node600);
  
  TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,&node400);
}