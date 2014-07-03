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


/////////////////////////////////////////////////
// Test avlAdd
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


/////////////////////////////////////////////////
// Test avlGetReplacer
/////////////////////////////////////////////////

// My own test cases

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
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=&Node150, .rightChild=&Node220};
	Node Node50 = {.data=50, .balance=1, .leftChild=&Node25, .rightChild=&Node200};
	
	Node *root = &Node50;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node220, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node200, 1, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node150, NULL, -1, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
  Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node50 = {.data=50, .balance=0, .leftChild=&Node40, .rightChild=&Node75};
  Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
  Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	
	Node *root = &Node100;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node200, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node40, 0, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node75, &Node150, 0, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
  Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node50 = {.data=50, .balance=1, .leftChild=NULL, .rightChild=&Node75};
  Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
  Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	
	Node *root = &Node100;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node200, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node75, &Node150, 0, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
  Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node50 = {.data=50, .balance=-1, .leftChild=&Node40, .rightChild=NULL};
  Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
  Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	
	Node *root = &Node100;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node200, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node40, 0, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node150, 1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
  Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
  Node Node75 = {.data=75, .balance=-1, .leftChild=&Node50, .rightChild=NULL};
  Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node40 = {.data=40, .balance=0, .leftChild=&Node25, .rightChild=&Node75};
  Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node40, .rightChild=&Node150};
	
	Node *root = &Node100;
	Node *replacerNode;
	
	replacerNode = avlGetReplacer(&root);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(replacerNode);
	TEST_ASSERT_EQUAL_PTR(&Node40, root);
	TEST_ASSERT_EQUAL_PTR(&Node200, replacerNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 1, &Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node75, &Node150, -1, &Node100);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node50, NULL, -1, &Node75);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
}


/////////////////////////////////////////////////
// Test avlRemove
/////////////////////////////////////////////////

// My own test cases

/*
 *    1 (Node to remove)
 */
void test_avlRemove_Node1_from_1_element_AVL_tree() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = &Node1;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node1);
	
	TEST_ASSERT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL_PTR(&Node1, removedNode);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
}

/*
 *    1 (Node to remove)
 *     \
 *     50
 */
void test_avlRemove_Node1_from_2_elements_AVL_tree() {
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&Node50};
	
	Node *root = &Node1;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node1);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, removedNode);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
}

/*
 *    1
 *     \
 *     50 (Node to remove)
 */
void test_avlRemove_Node50_from_2_elements_AVL_tree() {
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&Node50};
	
	Node *root = &Node1;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node50);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node1, root);
  TEST_ASSERT_EQUAL_PTR(&Node50, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
}


// Email requirements test cases

////////////////////////////////////////////////////////////
// Test avlRemove() on deletion of node on the left subtree
////////////////////////////////////////////////////////////

/*
 *      50  => NULL
 *
 * where 50 is being removed 
 */
void test_avlRemove_for_left_subtree_case_1() {
	Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = &Node50;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node50);
	
	TEST_ASSERT_NULL(root);
  TEST_ASSERT_NOT_NULL(removedNode);
  TEST_ASSERT_EQUAL_PTR(&Node50, removedNode);
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
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node50 = {.data=50, .balance=1, .leftChild=&Node25, .rightChild=&Node150};
  Node Node1= {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = &Node50;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node1);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NULL(removedNode); // Node1 cannot be found in the tree
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node150, 1, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node200, 1, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
}

/*
 *      50             50
 *     /  \     =>       \
 *   25   150            150
 *
 * where 25 is being removed
 */
void test_avlRemove_for_left_subtree_case_3() {
	Node Node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node50;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node25);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node150, 1, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node50 = {.data=50, .balance=1, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node50;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node25);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node150, root);
  TEST_ASSERT_EQUAL_PTR(&Node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node50, &Node200, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
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
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node50;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node25);
  
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
  
  // printf("show Node1 balance:%d\n", Node1.balance);
  // printf("=== END ===\n");
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node150, 1, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node200, 1, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
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
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node175 = {.data=175, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=&Node120, .rightChild=&Node175};
	Node Node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=-1, .leftChild=&Node150, .rightChild=&Node220};
	Node Node100 = {.data=100, .balance=1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node100;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node150, root);
  TEST_ASSERT_EQUAL_PTR(&Node1, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node100, &Node200, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node120, 0, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node175, &Node220, 0, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node120);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node175);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node220);
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
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=-1, .leftChild=&Node120, .rightChild=NULL};
	Node Node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=-1, .leftChild=&Node150, .rightChild=&Node220};
	Node Node100 = {.data=100, .balance=1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node100;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node150, root);
  TEST_ASSERT_EQUAL_PTR(&Node1, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node100, &Node200, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node120, 0, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node220, 1, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node120);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node220);
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
	Node Node175 = {.data=175, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node175};
	Node Node220 = {.data=220, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=-1, .leftChild=&Node150, .rightChild=&Node220};
	Node Node100 = {.data=100, .balance=1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node100;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node150, root);
  TEST_ASSERT_EQUAL_PTR(&Node1, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node100, &Node200, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, NULL, -1, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node175, &Node220, 0, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node175);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node220);
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
	Node Node175 = {.data=175, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node175};
	Node Node220 = {.data=220, .balance=1, .leftChild=NULL, .rightChild=&Node250};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=&Node150, .rightChild=&Node220};
	Node Node100 = {.data=100, .balance=1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node100;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node1);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node200, root);
  TEST_ASSERT_EQUAL_PTR(&Node1, removedNode);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node100, &Node220, -1, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node150, 1, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node250, 1, &Node220);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node175, 1, &Node150);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node175);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node250);
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
	Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=1, .leftChild=NULL, .rightChild=&Node40};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node50;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node25);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node40, &Node200, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
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
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=0, .leftChild=&Node1, .rightChild=&Node40};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node50;
	Node *removedNode;
	
	removedNode = avlRemove(&root, &Node25);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node25, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node200, -1, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node40, 1, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
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
	Node Node90 = {.data=90, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=1, .leftChild=NULL, .rightChild=&Node90};
	Node Node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
	Node Node200 = {.data=200, .balance=1, .leftChild=NULL, .rightChild=&Node250};
	Node Node150 = {.data=150, .balance=-1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node150;
	Node *removedNode;

  removedNode = avlRemove(&root, &Node150);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node90, root);
  TEST_ASSERT_EQUAL_PTR(&Node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node200, 0, &Node90);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node50, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node250, 1, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node250);
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
	Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node90 = {.data=90, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node40, .rightChild=&Node90};
	Node Node250 = {.data=250, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
	Node Node200 = {.data=200, .balance=1, .leftChild=NULL, .rightChild=&Node250};
	Node Node150 = {.data=150, .balance=-1, .leftChild=&Node25, .rightChild=&Node200};
	Node *root = &Node150;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node150);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node90, root);
  TEST_ASSERT_EQUAL_PTR(&Node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node200, -1, &Node90);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node50, 1, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node250, 1, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node40, NULL, -1, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node250);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
}


/////////////////////////////////////////////////////////////
// Test avlRemove() on deletion of node on the right subtree
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
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node *root = &Node50;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node200);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node150, -1, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
}
 
/*
 *      50             50
 *     /  \     =>    /
 *   25   150       25
 *
 * where 150 is being removed
 */
void test_avlRemove_for_right_subtree_case_2() {
	Node Node25 = {.data=25, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node50;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node150);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node150, removedNode);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, NULL, -1, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node50;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node150);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node25, root);
  TEST_ASSERT_EQUAL_PTR(&Node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node50, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node50;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node150);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node150, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node200, -1, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
	Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node40, .rightChild=&Node75};
	Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node100;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node200);

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node40, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node75, &Node150, 0, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=1, .leftChild=NULL, .rightChild=&Node75};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node100;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node200);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node75, &Node150, 0, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node75);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
	Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-1, .leftChild=&Node40, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node25 = {.data=25, .balance=1, .leftChild=&Node1, .rightChild=&Node50};
	Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node25, .rightChild=&Node150};
	Node *root = &Node100;
	Node *removedNode;

	removedNode = avlRemove(&root, &Node200);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 0, &Node50);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, &Node40, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node150, 1, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
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
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node50 = {.data=50, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node25 = {.data=25, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
  Node Node75 = {.data=75, .balance=-1, .leftChild=&Node50, .rightChild=NULL};
  Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
  Node Node40 = {.data=40, .balance=0, .leftChild=&Node25, .rightChild=&Node75};
  Node Node150 = {.data=150, .balance=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node40, .rightChild=&Node150};
  Node *root = &Node100;
  Node *removedNode;  
  
	removedNode = avlRemove(&root, &Node200);
  
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node40, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node100, 1, &Node40);
	TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node75, &Node150, -1, &Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node50, NULL, -1, &Node75);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
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
  Node Node150 = {.data = 150, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node25 = {.data = 25, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node200 = {.data = 200, .balance = -1, .leftChild = &Node150, .rightChild = NULL};
  Node Node50 = {.data = 50, .balance = 1, .leftChild = &Node25, .rightChild = &Node200};
  Node *root = &Node50;
	Node *removedNode;
	
  removedNode = avlRemove(&root,&Node200);
  
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node150, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
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
  Node Node150 = {.data = 150, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node25 = {.data = 25, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node220 = {.data = 220, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node200 = {.data = 200, .balance = 0, .leftChild = &Node150, .rightChild = &Node220};
  Node Node50 = {.data = 50, .balance = 1, .leftChild = &Node25, .rightChild = &Node200};
  Node *root = &Node50;
	Node *removedNode;
	
  removedNode = avlRemove(&root,&Node200);
  
 	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node150, 1, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, &Node220, 1, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node220);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
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
  Node Node1 = {.data = 1, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node250 = {.data = 250, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node175 = {.data = 175, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node150 = {.data = 150, .balance = 1, .leftChild = NULL, .rightChild = &Node175};
  Node Node200 = {.data = 200, .balance = -1, .leftChild = &Node150, .rightChild = &Node250};
  Node Node25 = {.data = 25, .balance = -1, .leftChild = &Node1, .rightChild = NULL};
  Node Node50 = {.data = 50, .balance = 1, .leftChild = &Node25, .rightChild = &Node200};
  Node *root = &Node50;
	Node *removedNode;
	
  removedNode = avlRemove(&root,&Node200);
  
 	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25, &Node175, 0, &Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node1, NULL, -1, &Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node150, &Node250, 0, &Node175);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node250);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL, NULL, 0, &Node200);
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
  Node Node1 = {.data = 1, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node250 = {.data = 250, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node175 = {.data = 175, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node120 = {.data = 120, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node150 = {.data = 150, .balance = 0, .leftChild = &Node120, .rightChild = &Node175};
  Node Node200 = {.data = 200, .balance = -1, .leftChild = &Node150, .rightChild = &Node250};
  Node Node25 = {.data = 25, .balance = -1, .leftChild = &Node1, .rightChild = NULL};
  Node Node50 = {.data = 50, .balance = 1, .leftChild = &Node25, .rightChild = &Node200};
  Node *root = &Node50;
	Node *removedNode;
  
  removedNode = avlRemove(&root,&Node200);

  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
  TEST_ASSERT_EQUAL_PTR(&Node200, removedNode);  
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25,&Node175,1,&Node50);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node1,NULL,-1,&Node25);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node150,&Node250,-1,&Node175);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node120,NULL,-1,&Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node1);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node120);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node250);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node200);
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
Node Node40 = {.data = 40, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node65 = {.data = 65, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node120 = {.data = 120, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node220 = {.data = 220, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node270 = {.data = 270, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node330 = {.data = 330, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node450 = {.data = 450, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node600 = {.data = 600, .balance = 0, .leftChild = NULL, .rightChild = NULL};
  Node Node25 = {.data = 25, .balance = 1, .leftChild = NULL, .rightChild = &Node40};
  Node Node150 = {.data = 150, .balance = -1, .leftChild = &Node120, .rightChild = NULL};
  Node Node200 = {.data = 200, .balance = 1, .leftChild = NULL, .rightChild = &Node220};
  Node Node350 = {.data = 350, .balance = -1, .leftChild = &Node330, .rightChild = NULL};
  Node Node550 = {.data = 550, .balance = 1, .leftChild = NULL, .rightChild = &Node600};
  Node Node300 = {.data = 300, .balance = 1, .leftChild = &Node270, .rightChild = &Node350};
  Node Node500 = {.data = 500, .balance = 1, .leftChild = &Node450, .rightChild = &Node550};
  Node Node50 = {.data = 50, .balance = -1, .leftChild = &Node25, .rightChild = &Node65};
  Node Node250 = {.data = 250, .balance = 1, .leftChild = &Node200, .rightChild = &Node300};
  Node Node100 = {.data = 100, .balance = -1, .leftChild = &Node50, .rightChild = &Node150};
  Node Node400 = {.data = 400, .balance = -1, .leftChild = &Node250, .rightChild = &Node500};
  Node Node175 = {.data = 175, .balance = 1, .leftChild = &Node100, .rightChild = &Node400};
  Node *root = &Node175;
	Node *removedNode;
	
  removedNode = avlRemove(&root,&Node400);
  
  TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(removedNode);
	TEST_ASSERT_EQUAL_PTR(&Node175, root);
  TEST_ASSERT_EQUAL_PTR(&Node400, removedNode);  
  
  TEST_ASSERT_EQUAL_AVL_NODE(&Node100,&Node350,0,&Node175);
  
  TEST_ASSERT_EQUAL_AVL_NODE(&Node50,&Node150,-1,&Node100);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node250,&Node500,0,&Node350);
  
  TEST_ASSERT_EQUAL_AVL_NODE(&Node450,&Node550,1,&Node500);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node200,&Node300,0,&Node250);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node25,&Node65,-1,&Node50);
  
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,&Node600,1,&Node550);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node270,&Node330,0,&Node300);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,&Node220,1,&Node200);
  TEST_ASSERT_EQUAL_AVL_NODE(&Node120,NULL,-1,&Node150);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,&Node40,1,&Node25);
  
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node40);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node65);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node120);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node220);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node270);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node330);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node450);
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node600);
  
  TEST_ASSERT_EQUAL_AVL_NODE(NULL,NULL,0,&Node400);
}