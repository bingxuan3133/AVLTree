#include "unity.h"
#include "Rotation.h"
#include "mock_getHeight.h"
#include "AVL.h"
#include "AVLInt.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/////////////////////////////////////////////////
// Test getHeight
/////////////////////////////////////////////////

/**
 *		(1)
 */
void test_getHeight_should_return_1_when_length_of_the_tree_is_1() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	
	int result = getHeight((Node *)&node1);
	
	TEST_ASSERT_EQUAL(1, result);
}

/**
 *		(1)
 *		  \
 *		  (2)
 *			  \
 *			  (3)
 */
void test_getHeight_should_get_the_longest_path_of_a_tree() {
	NodeInt node3 = {.data=3, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node2 = {.data=2, .balance=1, .leftChild=NULL, .rightChild=&node3};
	NodeInt node1 = {.data=1, .balance=2, .leftChild=NULL, .rightChild=&node2};
	
	_getHeight_ExpectAndReturn((Node *)&node2, 2);
	
	int result = getHeight((Node *)&node1);
	
	TEST_ASSERT_EQUAL(3, result);
}

/**
 *			(3)
 *      / \
 *		(2) (4)
 *    /
 *	(1)
 */
void test_getHeight_should_return_3_when_the_longest_path_of_the_tree_is_3() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node4 = {.data=4, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node2 = {.data=2, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node3 = {.data=3, .balance=-1, .leftChild=&node2, .rightChild=&node4};
	
	_getHeight_ExpectAndReturn((Node *)&node2, 2);
	_getHeight_ExpectAndReturn((Node *)&node4, 1);
	
	int result = getHeight((Node *)&node3);
	
	TEST_ASSERT_EQUAL(3, result);
}


// === ROTATION ===

// === SINGLE LEFT ROTATION ===
/////////////////////////////////////////////////
// Test leftRotate
/////////////////////////////////////////////////

/**
 *		(1)	+1		      (2) -1
 *		  \		    =>    /
 *		  (2)	0	      (1) 0
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos1_and_0_should_get_0_and_neg1() {
	NodeInt node2 = {.data=2, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=+1, .leftChild=NULL, .rightChild=&node2};
	
	NodeInt *root;
	
	root = (NodeInt *) leftRotate((Node *)&node1);
	TEST_ASSERT_EQUAL_PTR(&node2, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild);
	
	TEST_ASSERT_EQUAL(-1, node2.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
}

/**
 *		(1) +2              (2) 0
 *      \			            / \
 *		  (2) +1    =>	0 (1)	(3) 0
 *			  \
 *			  (3) 0
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos2_and_pos1_should_get_0_and_0() {
	NodeInt node3 = {.data=3, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node2 = {.data=2, .balance=1, .leftChild=NULL, .rightChild=&node3};
	NodeInt node1 = {.data=1, .balance=2, .leftChild=NULL, .rightChild=&node2};
	
	NodeInt *root;
	
	root = (NodeInt *) leftRotate((Node *)&node1);
	TEST_ASSERT_EQUAL_PTR(&node2, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node2.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node3.balance);
}

/**
 *			(50)  +2                  (100) 0
 *			/  \					            /	  \
 *   (10) (100) +1				   0 (50)  (150)
 *			  /	  \			  =>       /  \		  \
 *      (70)  (150)		  	  (10)  (70)  (200)
 *			  \
 *			 (200)
 */
void test_leftRotate_6_elements_given_balance_of_parent_and_rightChild_is_pos2_and_pos1_should_get_0_and_0() {
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=+1, .leftChild=NULL, .rightChild=&node200};
	NodeInt node70 = {.data=70, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=+1, .leftChild=&node70, .rightChild=&node150};
	NodeInt node10 = {.data=10, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=+2, .leftChild=&node10, .rightChild=&node100};

	NodeInt *root;
	
	root = (NodeInt *) leftRotate((Node *)&node50);
	TEST_ASSERT_EQUAL_PTR(&node100, root);
	TEST_ASSERT_EQUAL_PTR(&node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node10, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node70, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node200, root->rightChild->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild->rightChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node100.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(+1, node150.balance);
	TEST_ASSERT_EQUAL(0, node10.balance);
	TEST_ASSERT_EQUAL(0, node70.balance);
	TEST_ASSERT_EQUAL(0, node200.balance);
}

/**
 *			    100 +1                   150  -1
 *			  /	    \                   /	  \
 *		  50		  150 +1      -1  100     200
 *		 /	\	   /  \		  =>     /  \	    /
 *		1	  75 120  200			   50  120   180	
 *                /         / \
 *					    180			   1  75
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos1_and_pos1_should_get_neg1_and_neg1() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node1, .rightChild=&node75};
	NodeInt node180 = {.data=180, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=-1, .leftChild=&node180, .rightChild=NULL};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=+1, .leftChild=&node120, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=+1, .leftChild=&node50, .rightChild=&node150};
	
	NodeInt *root;
	
	root = (NodeInt *) leftRotate((Node *)&node100);
	TEST_ASSERT_EQUAL_PTR(&node150, root);
	TEST_ASSERT_EQUAL_PTR(&node100, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node200, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node50, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node120, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node180, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node75, root->leftChild->leftChild->rightChild);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node75.leftChild);
	TEST_ASSERT_NULL(node75.rightChild);
	TEST_ASSERT_NULL(node120.leftChild);
	TEST_ASSERT_NULL(node120.rightChild);
	TEST_ASSERT_NULL(node200.rightChild);
	TEST_ASSERT_NULL(node180.leftChild);
	TEST_ASSERT_NULL(node180.rightChild);

	
	TEST_ASSERT_EQUAL(-1, node100.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(-1, node150.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node75.balance);
	TEST_ASSERT_EQUAL(0, node120.balance);
	TEST_ASSERT_EQUAL(-1, node200.balance);
	TEST_ASSERT_EQUAL(0, node180.balance);
}

/**
 *		      100	+1  				        150 -2
 *			  /	   \                  /	    \
 *		  50		 150  -1        0 100	    200
 *     / \	  /   \		  =>     /	\
 *		1  75  120  200         50  120
 *				    \              /	\   \	
 *            130           1   75  130
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos1_and_neg1_should_get_0_and_neg2() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node1, .rightChild=&node75};
	NodeInt node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node120 = {.data=120, .balance=+1, .leftChild=NULL, .rightChild=&node130};
	NodeInt node150 = {.data=150, .balance=-1, .leftChild=&node120, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=+1, .leftChild=&node50, .rightChild=&node150};
	
	NodeInt *root;
	
	root = (NodeInt *) leftRotate((Node *)&node100);
	TEST_ASSERT_EQUAL_PTR(&node150, root);
	TEST_ASSERT_EQUAL_PTR(&node100, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node200, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node50, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node120, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node75, root->leftChild->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node130, root->leftChild->rightChild->rightChild);
	
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node75.leftChild);
	TEST_ASSERT_NULL(node75.rightChild);
	TEST_ASSERT_NULL(node120.leftChild);
	TEST_ASSERT_NULL(node200.leftChild);
	TEST_ASSERT_NULL(node200.rightChild);
	TEST_ASSERT_NULL(node130.leftChild);
	TEST_ASSERT_NULL(node130.rightChild);

	
	TEST_ASSERT_EQUAL(-2, node150.balance);
	TEST_ASSERT_EQUAL(0, node100.balance);
	TEST_ASSERT_EQUAL(0, node200.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(+1, node120.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node75.balance);
	TEST_ASSERT_EQUAL(0, node130.balance);
}


// === SINGLE RIGHT ROTATION ===
/////////////////////////////////////////////////
// Test rightRotate
/////////////////////////////////////////////////

/**
 *		  (2)	-1	      (1) +1
 *		  /		    =>	    \
 *		(1) 0             (2) 0
 */
void test_rightRotate_given_balance_of_parent_and_rightChild_is_neg1_and_0_should_get_0_and_pos1() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node2 = {.data=2, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	
	NodeInt *root;
	
	root = (NodeInt *) rightRotate((Node *)&node2);
	TEST_ASSERT_EQUAL_PTR(&node1, root);
	TEST_ASSERT_EQUAL_PTR(&node2, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node2.balance);
	TEST_ASSERT_EQUAL(1, node1.balance);
}

/**
 *			  (3)	-2	          (2) 0
 *		  	/                 / \
 *		  (2)	-1     => 	0 (1)	(3)
 *		  /
 *		(1)
 */
void test_rightRotate_given_balance_of_parent_and_leftChild_is_neg2_and_neg1_should_get_0_and_0() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node2 = {.data=2, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node3 = {.data=3, .balance=-2, .leftChild=&node2, .rightChild=NULL};
	
	NodeInt *root;
	
	root = (NodeInt *) rightRotate((Node *)&node3);
	TEST_ASSERT_EQUAL_PTR(&node2, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node2.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node3.balance);
}

/**
 *			      (50) -2 			        (10)  0
 *			     /    \				          /  \
 *      -1 (10) (100)	            (5) (50)  0
 *        /   \           =>      /   /   \
 *      (5)  (30)			          (1) (30) (100)
 *	   /
 *	 (1)
 */
void test_rightRotate_6_elements_given_balance_of_parent_and_leftChild_is_neg2_and_neg1_should_get_0_and_0() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node5 = {.data=5, .balance=-1, .leftChild=&node1, .rightChild=NULL};
	NodeInt node30 = {.data=30, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node10 = {.data=10, .balance=-1, .leftChild=&node5, .rightChild=&node30};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-2, .leftChild=&node10, .rightChild=&node100};

	NodeInt *root;
	
	root = (NodeInt *) rightRotate((Node *)&node50);
	TEST_ASSERT_EQUAL_PTR(&node10, root);
	TEST_ASSERT_EQUAL_PTR(&node5, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node50, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node30, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node100, root->rightChild->rightChild);
	
	TEST_ASSERT_NULL(node5.rightChild);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node30.leftChild);
	TEST_ASSERT_NULL(node30.rightChild);
	TEST_ASSERT_NULL(node100.leftChild);
	TEST_ASSERT_NULL(node100.rightChild);
		
	TEST_ASSERT_EQUAL(0, node10.balance);
	TEST_ASSERT_EQUAL(-1, node5.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node30.balance);
	TEST_ASSERT_EQUAL(0, node100.balance);
}

/**
 *				    150 -1               100  +1
 *          /	    \               /   \
 *    -1  100     200            50	  150 +1
 *       /  \	    /      =>     / \    / \
 *      50  120 180			       1  75 120	200
 *     / \								                /
 *    1   75                           180
 */
void test_rightRotate_given_balance_of_parent_and_leftChild_is_neg1_and_neg1_should_get_pos1_and_pos1() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=0, .leftChild=&node1, .rightChild=&node75};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node180 = {.data=180, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node50, .rightChild=&node120};
	NodeInt node200 = {.data=200, .balance=-1, .leftChild=&node180, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=-1, .leftChild=&node100, .rightChild=&node200};
	
	NodeInt *root;
	
	root = (NodeInt *) rightRotate((Node *)&node150);
	TEST_ASSERT_EQUAL_PTR(&node100, root);
	TEST_ASSERT_EQUAL_PTR(&node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node75, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node120, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node200, root->rightChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node180, root->rightChild->rightChild->leftChild);
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node75.leftChild);
	TEST_ASSERT_NULL(node75.rightChild);
	TEST_ASSERT_NULL(node120.leftChild);
	TEST_ASSERT_NULL(node120.rightChild);
	TEST_ASSERT_NULL(node200.rightChild);
	TEST_ASSERT_NULL(node180.leftChild);
	TEST_ASSERT_NULL(node180.rightChild);

	
	TEST_ASSERT_EQUAL(+1, node100.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(+1, node150.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node75.balance);
	TEST_ASSERT_EQUAL(0, node120.balance);
	TEST_ASSERT_EQUAL(-1, node200.balance);
	TEST_ASSERT_EQUAL(0, node180.balance);
}

/**
 *          100  -1               50  +2
 *			 /	    \                 / \
 *  +1  50		  150              1  100 0
 *     /  \	    /   \		  =>        /  \
 *		1	  75  120		200           75  150
 *			  /								        /   / \
 *		  60                      60	120	200
 */
void test_rightRotate_given_balance_of_parent_and_leftChild_is_neg1_and_pos1_should_get_pos2_and_0() {
	NodeInt node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node60 = {.data=60, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node75 = {.data=75, .balance=-1, .leftChild=&node60, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=+1, .leftChild=&node1, .rightChild=&node75};
	NodeInt node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node150 = {.data=150, .balance=0, .leftChild=&node120, .rightChild=&node200};
	NodeInt node100 = {.data=100, .balance=-1, .leftChild=&node50, .rightChild=&node150};
	
	NodeInt *root;
	
	root = (NodeInt *) rightRotate((Node *)&node100);
	TEST_ASSERT_EQUAL_PTR(&node50, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node100, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node75, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node150, root->rightChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node60, root->rightChild->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node120, root->rightChild->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node200, root->rightChild->rightChild->rightChild);
	
	TEST_ASSERT_NULL(node1.leftChild);
	TEST_ASSERT_NULL(node1.rightChild);
	TEST_ASSERT_NULL(node60.leftChild);
	TEST_ASSERT_NULL(node60.rightChild);
	TEST_ASSERT_NULL(node75.rightChild);
	TEST_ASSERT_NULL(node120.leftChild);
	TEST_ASSERT_NULL(node120.rightChild);
	TEST_ASSERT_NULL(node200.leftChild);
	TEST_ASSERT_NULL(node200.rightChild);

	
	TEST_ASSERT_EQUAL(2, node50.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node100.balance);
	TEST_ASSERT_EQUAL(-1, node75.balance);
	TEST_ASSERT_EQUAL(0, node150.balance);
	TEST_ASSERT_EQUAL(0, node60.balance);
	TEST_ASSERT_EQUAL(0, node120.balance);
	TEST_ASSERT_EQUAL(0, node200.balance);
}


// === DOUBLE LEFT ROTATION ===
/////////////////////////////////////////////////
// Test doubleLeftRotate
/////////////////////////////////////////////////

/**
 *    (1)           (2)
 *      \		        / \
 *      (3)	  =>	(1)	(3)
 *      /
 *    (2)
 */
void test_doubleLeftRotate_given_3_elements_should_rotate_to_balance_tree() {
	NodeInt node2 = {.data=2, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node3 = {.data=3, .balance=-1, .leftChild=&node2, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=2, .leftChild=NULL, .rightChild=&node3};
	
	NodeInt *root;
	
	root = (NodeInt *) doubleLeftRotate((Node *)&node1);
	TEST_ASSERT_EQUAL_PTR(&node2, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node2.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node3.balance);
}


// === DOUBLE RIGHT ROTATION ===
/////////////////////////////////////////////////
// Test doubleRightRotate
/////////////////////////////////////////////////

/**
 *		  (3)		    (2)
 *		  /			    / \
 *		(1)		=>	(1)	(3)
 *		  \
 *		  (2)
 */
void test_doubleRightRotate_given_3_elements_should_rotate_to_balance_tree() {
	NodeInt node2 = {.data=2, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&node2};
	NodeInt node3 = {.data=3, .balance=-2, .leftChild=&node1, .rightChild=NULL};
	
	NodeInt *root;
	
	root = (NodeInt *) doubleRightRotate((Node *)&node3);
	TEST_ASSERT_EQUAL_PTR(&node2, root);
	TEST_ASSERT_EQUAL_PTR(&node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, node2.balance);
	TEST_ASSERT_EQUAL(0, node1.balance);
	TEST_ASSERT_EQUAL(0, node3.balance);
}

/**
 *			  (50)				     (30)
 *			  /  \				    /   \
 *		 (10) (100)       (10)	(50)
 *		 /	\	  		=>    /	    /  \
 *    (5) (30)        (5)  (40)  (100)
 *          \
 *          (40)
 */
void test_doubleRightRotate_given_6_elements_should_rotate_to_balance_tree() {
	NodeInt node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node5 = {.data=5, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node30 = {.data=30, .balance=1, .leftChild=NULL, .rightChild=&node40};
	NodeInt node10 = {.data=10, .balance=1, .leftChild=&node5, .rightChild=&node30};
	NodeInt node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	NodeInt node50 = {.data=50, .balance=-2, .leftChild=&node10, .rightChild=&node100};

	NodeInt *root;
	
	root = (NodeInt *) doubleRightRotate((Node *)&node50);
	TEST_ASSERT_EQUAL_PTR(&node30, root);
	TEST_ASSERT_EQUAL_PTR(&node10, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node50, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&node5, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node40, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&node100, root->rightChild->rightChild);

	TEST_ASSERT_NULL(node10.rightChild);
	TEST_ASSERT_NULL(node5.leftChild);
	TEST_ASSERT_NULL(node5.rightChild);
	TEST_ASSERT_NULL(node40.leftChild);
	TEST_ASSERT_NULL(node40.rightChild);
	TEST_ASSERT_NULL(node100.leftChild);
	TEST_ASSERT_NULL(node100.rightChild);
	
	TEST_ASSERT_EQUAL(0, node30.balance);
	TEST_ASSERT_EQUAL(-1, node10.balance);
	TEST_ASSERT_EQUAL(0, node50.balance);
	TEST_ASSERT_EQUAL(0, node5.balance);
	TEST_ASSERT_EQUAL(0, node40.balance);
	TEST_ASSERT_EQUAL(0, node100.balance);
}


