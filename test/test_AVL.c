#include "unity.h"
#include "Rotation.h"
#include "getHeight.h"
#include "AVL.h"
#include "CustomAssert.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// avlAdd
// ======

/*
 *		  100 (1)
 *	   /   \
 *	 50		150 (-1 -> 0)
 *		   /   \
 *		120   *200
 *
 *	*nodeToAdd
 */
void test_avlAdd_focus_on_balance_factor_while_tree_height_remains_case_1() {
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=-1, .leftChild=&Node120, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=1, .leftChild=&Node50, .rightChild=&Node150};
	
	Node *root = &Node100;
	
	root = avlAdd(root, &Node200);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&Node100, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node120, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node200.balance);
	TEST_ASSERT_EQUAL(0, Node120.balance);
	TEST_ASSERT_EQUAL(0, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(1, Node100.balance);
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
void test_avlAdd_focus_on_balance_factor_while_tree_height_remains_case_2() {
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=1, .leftChild=&Node50, .rightChild=&Node150};
	
	Node *root = &Node100;
	
	root = avlAdd(root, &Node120);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&Node100, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node120, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node200.balance);
	TEST_ASSERT_EQUAL(0, Node120.balance);
	TEST_ASSERT_EQUAL(0, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(1, Node100.balance);
}

/*
 *		1 (0 -> 1)
 *		 \
 *		 *50
 *
 *	*nodeToAdd
 */
void test_avlAdd_focus_on_balance_factor_while_tree_height_changes_case_1() {
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	
	Node *root = &Node1;
	
	root = avlAdd(root, &Node50);
	
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node50, 1, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
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
void test_avlAdd_focus_on_balance_factor_while_tree_height_changes_case_2() {
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=&Node50, .rightChild=&Node150};
	
	Node *root = &Node100;
	
	root = avlAdd(root, &Node120);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node150, 1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node120, NULL, -1, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node120);
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
void test_avlAdd_focus_on_balance_factor_while_tree_height_changes_case_3() {
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=&Node50, .rightChild=&Node150};
	
	Node *root = &Node100;
	
	root = avlAdd(root, &Node200);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node150, 1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node200, 1, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
}

/*
 *		1
 */
void test_avlAdd_1() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	
	TEST_ASSERT_EQUAL(0, Node1.balance);
}

/*
 *		1
 *		 \
 *		 50	
 */
void test_avlAdd_1_50() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->rightChild);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node50.leftChild);
	TEST_ASSERT_NULL(Node50.rightChild);
	
	TEST_ASSERT_EQUAL(1, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
}

/*
 *		1
 *		 \					50
 *		 50		=>	 /  \
 *		  \				1	  100
 *			100
 */
void test_avlAdd_1_50_100() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->rightChild);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node100.leftChild);
	TEST_ASSERT_NULL(Node100.rightChild);
	
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(0, Node100.balance);
}

/*
 *		  50
 *	 	 /	\
 *		1	  100
 *			  /
 *		  75
 */
void test_avlAdd_1_50_100_75() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node75, root->rightChild->leftChild);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node100.rightChild);
	TEST_ASSERT_NULL(Node75.leftChild);
	TEST_ASSERT_NULL(Node75.rightChild);
	
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(1, Node50.balance);
	TEST_ASSERT_EQUAL(-1, Node100.balance);
	TEST_ASSERT_EQUAL(0, Node75.balance);
}

/*
 *		  50
 *	 	 /	\
 *		1	  100
 *			  / \
 *		  75  150
 */
void test_avlAdd_1_50_100_75_150() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	root = avlAdd(root, &Node150);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node75, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node150, root->rightChild->rightChild);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node75.leftChild);
	TEST_ASSERT_NULL(Node75.rightChild);
	TEST_ASSERT_NULL(Node150.leftChild);
	TEST_ASSERT_NULL(Node150.rightChild);
	
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(1, Node50.balance);
	TEST_ASSERT_EQUAL(0, Node100.balance);
	TEST_ASSERT_EQUAL(0, Node75.balance);
	TEST_ASSERT_EQUAL(0, Node150.balance);
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
void test_avlAdd_1_50_100_75_150_200() {
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	root = avlAdd(root, &Node150);
	root = avlAdd(root, &Node200);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node150, 0, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node75, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node200, 1, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
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
void test_avlAdd_1_50_100_75_150_200_120() {
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	root = avlAdd(root, &Node150);
	root = avlAdd(root, &Node200);
	root = avlAdd(root, &Node120);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node150, 0, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node75, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node120, &Node200, 0, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node120);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
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
void test_avlAdd_1_50_100_75_150_200_120_110() {
	Node Node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	root = avlAdd(root, &Node150);
	root = avlAdd(root, &Node200);
	root = avlAdd(root, &Node120);
	root = avlAdd(root, &Node110);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node150, 1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node75, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node120, &Node200, -1, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node110, NULL, -1, &Node120);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node110);
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
void test_avlAdd_1_50_100_75_150_200_120_110_130() {
	Node Node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	root = avlAdd(root, &Node150);
	root = avlAdd(root, &Node200);
	root = avlAdd(root, &Node120);
	root = avlAdd(root, &Node110);
	root = avlAdd(root, &Node130);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node150, 1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node75, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node120, &Node200, -1, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node110, &Node130, 0, &Node120);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node110);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node130);
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
void test_avlAdd_1_50_100_75_150_200_120_110_130_250() {
	Node Node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	root = avlAdd(root, &Node150);
	root = avlAdd(root, &Node200);
	root = avlAdd(root, &Node120);
	root = avlAdd(root, &Node110);
	root = avlAdd(root, &Node130);
	root = avlAdd(root, &Node250);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node150, 1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node75, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node120, &Node200, 0, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node110, &Node130, 0, &Node120);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node250, 1, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node110);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node130);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node250);
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
void test_avlAdd_1_50_100_75_150_200_120_110_130_250_140() {
	Node Node140 = {.data=140, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node110 = {.data=110, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = NULL;
	
	root = avlAdd(root, &Node1);
	root = avlAdd(root, &Node50);
	root = avlAdd(root, &Node100);
	root = avlAdd(root, &Node75);
	root = avlAdd(root, &Node150);
	root = avlAdd(root, &Node200);
	root = avlAdd(root, &Node120);
	root = avlAdd(root, &Node110);
	root = avlAdd(root, &Node130);
	root = avlAdd(root, &Node250);
	root = avlAdd(root, &Node140);
	
	TEST_ASSERT_EQUAL_AVL_NODE(&Node100, &Node150, 0, &Node120);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node110, -1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node130, &Node200, 0, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node75, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node110);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node140, 1, &Node130);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node250, 1, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node140);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node250);
}

// avlRemove
// ==============


// void test_avlRemove_Node1_from_1_element_AVL_tree() {
	// Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	// Node *root = &Node1;
	// Node *removedNode;
	
	// removedNode = avlRemove(&root, &Node1);
	
	// TEST_ASSERT_NULL(root);
	// TEST_ASSERT_NOT_NULL(removedNode);
// }

// void test_avlRemove_Node1_from_2_elements_AVL_tree() {
	// Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	// Node Node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&Node50};
	
	// Node *root = &Node1;
	// Node *removedNode;
	
	// removedNode = avlRemove(&root, &Node1);
	
	// TEST_ASSERT_NOT_NULL(root);
	// TEST_ASSERT_NOT_NULL(removedNode);
	
	// TEST_ASSERT_EQUAL_PTR(&Node50, root);
	// TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
	
	// TEST_ASSERT_EQUAL_PTR(&Node1, removedNode);
	// TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
// }

// void test_avlRemove_Node50_from_2_elements_AVL_tree() {
	// Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	// Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=&Node50};
	
	// Node *root = &Node1;
	// Node *removedNode;
	
	// removedNode = avlRemove(&root, &Node50);
	
	// TEST_ASSERT_NOT_NULL(root);
	// TEST_ASSERT_NOT_NULL(removedNode);
	// TEST_ASSERT_EQUAL_PTR(&Node1, root);
	// TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	
	// TEST_ASSERT_EQUAL_PTR(&Node50, removedNode);
	// TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
// }

// avlGetReplacer
// ==============

/*
 *		1 (Replacing node)
 */
void test_avlGetReplacer_case_1() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	
	Node *root = &Node1;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
}

/*
 *			50 (Replacing node)
 *		 /
 *		1
 */
void test_avlGetReplacer_case_2() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	
	Node *root = &Node50;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node1, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
}

/*
 *		1
 *		 \
 *			50 (Replacing node)
 */
void test_avlGetReplacer_case_3() {
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&Node50};
	
	Node *root = &Node1;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node1, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
}

/*
 *			50
 *     /  \
 *		1		100 (Replacing node)
 */
void test_avlGetReplacer_case_4() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node1, .rightChild=&Node100};
	
	Node *root = &Node50;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node100, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node100);
}

/*
 *			50
 *     /  \
 *		1		100 (Replacing node)
 *        /
 *      75
 */
void test_avlGetReplacer_case_5() {
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node75, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=1, .leftChild=&Node1, .rightChild=&Node100};
	
	Node *root = &Node50;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node100, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node75, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node100);
}

/*
 *			50
 *     /  \
 *		10	100
 *   /    / \
 *  1   75  200 (Replacing node)
 *          /
 *        150
 */
void test_avlGetReplacer_case_6() {
  Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node200 = {.data=200, .balance=-1, .leftChild=&Node150, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=1, .leftChild=&Node75, .rightChild=&Node200};
  Node Node10 = {.data=10, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=1, .leftChild=&Node10, .rightChild=&Node100};
	
	Node *root = &Node50;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node200, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node10, &Node100, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node10);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node75, &Node150, 0, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
 	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
}

/*
 *			 50                                  30
 *      /  \                                /  \
 *		10	 100                            10    50
 *   / \    \                       =>   / \   / \
 *  1  30   200 (Replacing node)        1  20 40 100
 *    / \ 
 *   20 40 
 */
void test_avlGetReplacer_case_7() {
  Node Node20 = {.data=20, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node30 = {.data=30, .balance=0, .leftChild=&Node20, .rightChild=&Node40};
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node10 = {.data=10, .balance=1, .leftChild=&Node1, .rightChild=&Node30};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node10, .rightChild=&Node100};
	
	Node *root = &Node50;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node30, root);
	TEST_ASSERT_EQUAL_PTR(&Node200, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node10, &Node50, 0, &Node30);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node20, 0, &Node10);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node40, &Node100, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node20);
 	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
}

/*
 *			 50                           10
 *      /  \                         /  \
 *		10	 100 (Replacing node) =>  1   50
 *   /
 *  1
 */
void test_avlGetReplacer_case_8() {
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node10 = {.data=10, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node10, .rightChild=&Node100};
	
	Node *root = &Node50;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node10, root);
	TEST_ASSERT_EQUAL_PTR(&Node100, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node50, 0, &Node10);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node100);
}
