#include "unity.h"
#include "Rotation.h"
#include "mock_getHeight.h"
#include "AVL.h"

void setUp(void)
{
}

void tearDown(void)
{
}


// === GET HEIGHT TEST ===

/**
 *		(1)
 */
void test_getHeight_should_return_1_when_length_of_the_tree_is_1() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	
	int result = getHeight(&Node1);
	
	TEST_ASSERT_EQUAL(1, result);
}

/**
 *		(1)
 *		  \
 *		  (2)
 *			\
 *			(3)
 */
void test_getHeight_should_get_the_longest_path_of_a_tree() {
	Node Node3 = {.data=3, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .balance=1, .leftChild=NULL, .rightChild=&Node3};
	Node Node1 = {.data=1, .balance=2, .leftChild=NULL, .rightChild=&Node2};
	
	_getHeight_ExpectAndReturn(&Node2, 2);
	
	int result = getHeight(&Node1);
	
	TEST_ASSERT_EQUAL(3, result);
}

/**
 *			(3)
 *			/ \
 *		 (2)  (4)
 *		 /
 *	  (1)
 */
void test_getHeight_should_return_3_when_the_longest_path_of_the_tree_is_3() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node4 = {.data=4, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node3 = {.data=3, .balance=-1, .leftChild=&Node2, .rightChild=&Node4};
	
	_getHeight_ExpectAndReturn(&Node2, 2);
	_getHeight_ExpectAndReturn(&Node4, 1);
	
	int result = getHeight(&Node3);
	
	TEST_ASSERT_EQUAL(3, result);
}

// === SINGLE LEFT ROTATION ===

/**
 *		(1)			  (2)
 *		  \		=>	  /
 *		  (2)		(1)
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos1_and_0_should_get_0_and_neg1() {
	Node Node2 = {.data=2, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=+1, .leftChild=NULL, .rightChild=&Node2};
	
	Node *root;
	
	root = leftRotate(&Node1);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild);
	
	TEST_ASSERT_EQUAL(-1, Node2.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
}

/**
 *		(1)			  (2)
 *		  \			  / \
 *		  (2)	=>	(1)	(3)
 *			\
 *			(3)
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos2_and_pos1_should_get_0_and_0() {
	Node Node3 = {.data=3, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .balance=1, .leftChild=NULL, .rightChild=&Node3};
	Node Node1 = {.data=1, .balance=2, .leftChild=NULL, .rightChild=&Node2};
	
	Node *root;
	
	root = leftRotate(&Node1);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node3.balance);
}

/**
 *			(50)					  (100)
 *			/  \					  /	  \
 *		 (10) (100)				   (50)	 (150)
 *			  /	  \			=>	   /  \		\
 *		   (70)	 (150)			(10)  (70) (200)
 *				 	\
 *				   (200)
 */
void test_leftRotate_6_elements_given_balance_of_parent_and_rightChild_is_pos2_and_pos1_should_get_0_and_0() {
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=+1, .leftChild=NULL, .rightChild=&Node200};
	Node Node70 = {.data=70, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=+1, .leftChild=&Node70, .rightChild=&Node150};
	Node Node10 = {.data=10, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=+2, .leftChild=&Node10, .rightChild=&Node100};

	Node *root;
	
	root = leftRotate(&Node50);
	TEST_ASSERT_EQUAL_PTR(&Node100, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node10, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node70, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->rightChild->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild->rightChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node100.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(+1, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node10.balance);
	TEST_ASSERT_EQUAL(0, Node70.balance);
	TEST_ASSERT_EQUAL(0, Node200.balance);
}

/**
 *			   100							 150
 *			 /	   \						/	\
 *		  50		150					 100	200
 *		 /	\	   /   \		=>		/  \	/
 *		1	75  120		200			  50  120  180	
 *					   /			 /	\
 *					180				1	75
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos1_and_pos1_should_get_neg1_and_neg1() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node1, .rightChild=&Node75};
	Node Node180 = {.data=180, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=-1, .leftChild=&Node180, .rightChild=NULL};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=+1, .leftChild=&Node120, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=+1, .leftChild=&Node50, .rightChild=&Node150};
	
	Node *root;
	
	root = leftRotate(&Node100);
	TEST_ASSERT_EQUAL_PTR(&Node150, root);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node120, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node180, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node75, root->leftChild->leftChild->rightChild);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node75.leftChild);
	TEST_ASSERT_NULL(Node75.rightChild);
	TEST_ASSERT_NULL(Node120.leftChild);
	TEST_ASSERT_NULL(Node120.rightChild);
	TEST_ASSERT_NULL(Node200.rightChild);
	TEST_ASSERT_NULL(Node180.leftChild);
	TEST_ASSERT_NULL(Node180.rightChild);

	
	TEST_ASSERT_EQUAL(-1, Node100.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(-1, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node75.balance);
	TEST_ASSERT_EQUAL(0, Node120.balance);
	TEST_ASSERT_EQUAL(-1, Node200.balance);
	TEST_ASSERT_EQUAL(0, Node180.balance);
}

/**
 *			   100							 150
 *			 /	   \						/	\
 *		  50		150					 100	200
 *		 /	\	   /   \		=>		/	\
 *		1	75  120		200			  50	120
 *				   \				 /	\	  \	
 *					130				1	75	  130
 */
void test_leftRotate_given_balance_of_parent_and_rightChild_is_pos1_and_neg1_should_get_0_and_neg2() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node1, .rightChild=&Node75};
	Node Node130 = {.data=130, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node120 = {.data=120, .balance=+1, .leftChild=NULL, .rightChild=&Node130};
	Node Node150 = {.data=150, .balance=-1, .leftChild=&Node120, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=+1, .leftChild=&Node50, .rightChild=&Node150};
	
	Node *root;
	
	root = leftRotate(&Node100);
	TEST_ASSERT_EQUAL_PTR(&Node150, root);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node120, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node75, root->leftChild->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node130, root->leftChild->rightChild->rightChild);
	
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node75.leftChild);
	TEST_ASSERT_NULL(Node75.rightChild);
	TEST_ASSERT_NULL(Node120.leftChild);
	TEST_ASSERT_NULL(Node200.leftChild);
	TEST_ASSERT_NULL(Node200.rightChild);
	TEST_ASSERT_NULL(Node130.leftChild);
	TEST_ASSERT_NULL(Node130.rightChild);

	
	TEST_ASSERT_EQUAL(-2, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node100.balance);
	TEST_ASSERT_EQUAL(0, Node200.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(+1, Node120.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node75.balance);
	TEST_ASSERT_EQUAL(0, Node130.balance);
}


// === SINGLE RIGHT ROTATION ===

/**
 *		  (2)		(1)
 *		  /		=>	  \
 *		(1)			  (2)
 */
void test_rightRotate_given_balance_of_parent_and_rightChild_is_neg1_and_0_should_get_0_and_pos1() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	
	Node *root;
	
	root = rightRotate(&Node2);
	TEST_ASSERT_EQUAL_PTR(&Node1, root);
	TEST_ASSERT_EQUAL_PTR(&Node2, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.balance);
	TEST_ASSERT_EQUAL(1, Node1.balance);
}

/**
 *			(3)		  (2)
 *		  	/	  	  / \
 *		  (2)	=>	(1)	(3)
 *		  /
 *		(1)
 */
void test_rightRotate_given_balance_of_parent_and_leftChild_is_neg2_and_neg1_should_get_0_and_0() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node3 = {.data=3, .balance=-2, .leftChild=&Node2, .rightChild=NULL};
	
	Node *root;
	
	root = rightRotate(&Node3);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node3.balance);
}

/**
 *			(50)				  (10)
 *			/  \				 /	 \
 *		 (10) (100)			   (5)	(50)
 *		 /	\	  		=>	   /	/  \
 *	   (5)  (30)			 (1) (30) (100)
 *	   /
 *	 (1)
 */
void test_rightRotate_6_elements_given_balance_of_parent_and_leftChild_is_neg2_and_neg1_should_get_0_and_0() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node5 = {.data=5, .balance=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node30 = {.data=30, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node10 = {.data=10, .balance=-1, .leftChild=&Node5, .rightChild=&Node30};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-2, .leftChild=&Node10, .rightChild=&Node100};

	Node *root;
	
	root = rightRotate(&Node50);
	TEST_ASSERT_EQUAL_PTR(&Node10, root);
	TEST_ASSERT_EQUAL_PTR(&Node5, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node30, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->rightChild->rightChild);
	
	TEST_ASSERT_NULL(Node5.rightChild);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node30.leftChild);
	TEST_ASSERT_NULL(Node30.rightChild);
	TEST_ASSERT_NULL(Node100.leftChild);
	TEST_ASSERT_NULL(Node100.rightChild);
		
	TEST_ASSERT_EQUAL(0, Node10.balance);
	TEST_ASSERT_EQUAL(-1, Node5.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node30.balance);
	TEST_ASSERT_EQUAL(0, Node100.balance);
}

/**
 *				 150				 100
 * 			    /	\				/	\
 *			 100	200			  50	 150
 *			/  \	/		=>	 / \	/  	\
 *		  50  120 180			1  75 120	200
 *		 /	\								/
 *		1	75							 180
 */
void test_rightRotate_given_balance_of_parent_and_rightChild_is_pos1_and_pos1_should_get_neg1_and_neg1() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=0, .leftChild=&Node1, .rightChild=&Node75};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node180 = {.data=180, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node50, .rightChild=&Node120};
	Node Node200 = {.data=200, .balance=-1, .leftChild=&Node180, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=-1, .leftChild=&Node100, .rightChild=&Node200};
	
	Node *root;
	
	root = rightRotate(&Node150);
	TEST_ASSERT_EQUAL_PTR(&Node100, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node75, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node120, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->rightChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node180, root->rightChild->rightChild->leftChild);
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node75.leftChild);
	TEST_ASSERT_NULL(Node75.rightChild);
	TEST_ASSERT_NULL(Node120.leftChild);
	TEST_ASSERT_NULL(Node120.rightChild);
	TEST_ASSERT_NULL(Node200.rightChild);
	TEST_ASSERT_NULL(Node180.leftChild);
	TEST_ASSERT_NULL(Node180.rightChild);

	
	TEST_ASSERT_EQUAL(+1, Node100.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(+1, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node75.balance);
	TEST_ASSERT_EQUAL(0, Node120.balance);
	TEST_ASSERT_EQUAL(-1, Node200.balance);
	TEST_ASSERT_EQUAL(0, Node180.balance);
}

/**
 *			   100							 50
 *			 /	   \						/	\
 *		  50		150					   1	100
 *		 /	\	   /   \		=>			   /  \
 *		1	75  120		200					 75	  150
 *			/								/  	  / \
 *		  60							  60	120	200
 */
void xtest_rightRotate_given_balance_of_parent_and_rightChild_is_pos1_and_neg1_should_get_0_and_neg2() {
	Node Node1 = {.data=1, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node60 = {.data=60, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node75 = {.data=75, .balance=-1, .leftChild=&Node60, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=+1, .leftChild=&Node1, .rightChild=&Node75};
	Node Node120 = {.data=120, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node200 = {.data=200, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .balance=0, .leftChild=&Node120, .rightChild=&Node200};
	Node Node100 = {.data=100, .balance=-1, .leftChild=&Node50, .rightChild=&Node150};
	
	Node *root;
	
	root = rightRotate(&Node100);
	TEST_ASSERT_EQUAL_PTR(&Node50, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node75, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node150, root->rightChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node60, root->rightChild->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node120, root->rightChild->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->leftChild->rightChild->rightChild);
	
	TEST_ASSERT_NULL(Node1.leftChild);
	TEST_ASSERT_NULL(Node1.rightChild);
	TEST_ASSERT_NULL(Node60.leftChild);
	TEST_ASSERT_NULL(Node60.rightChild);
	TEST_ASSERT_NULL(Node75.rightChild);
	TEST_ASSERT_NULL(Node120.leftChild);
	TEST_ASSERT_NULL(Node120.rightChild);
	TEST_ASSERT_NULL(Node200.leftChild);
	TEST_ASSERT_NULL(Node200.rightChild);

	
	TEST_ASSERT_EQUAL(2, Node50.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node100.balance);
	TEST_ASSERT_EQUAL(-1, Node75.balance);
	TEST_ASSERT_EQUAL(0, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node60.balance);
	TEST_ASSERT_EQUAL(0, Node120.balance);
	TEST_ASSERT_EQUAL(0, Node200.balance);
}

// === DOUBLE LEFT ROTATION ===

/**
 *		  (1)	  	  (2)
 *		  	\		  / \
 *			(3)	=>	(1)	(3)
 *		  	/
 *		  (2)
 */
void xtest_doubleLeftRotate_given_3_elements_should_rotate_to_balance_tree() {
	Node Node2 = {.data=2, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node3 = {.data=3, .balance=-1, .leftChild=&Node2, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=2, .leftChild=NULL, .rightChild=&Node3};
	
	Node *root;
	
	root = doubleLeftRotate(&Node1);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node3.balance);
}

// === DOUBLE RIGHT ROTATION ===

/**
 *		  (3)		  (2)
 *		  /			  / \
 *		(1)		=>	(1)	(3)
 *		  \
 *		  (2)
 */
void test_doubleRightRotate_given_3_elements_should_rotate_to_balance_tree() {
	Node Node2 = {.data=2, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .balance=1, .leftChild=NULL, .rightChild=&Node2};
	Node Node3 = {.data=3, .balance=-2, .leftChild=&Node1, .rightChild=NULL};
	
	Node *root;
	
	root = doubleRightRotate(&Node3);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.balance);
	TEST_ASSERT_EQUAL(0, Node1.balance);
	TEST_ASSERT_EQUAL(0, Node3.balance);
}

/**
 *			(50)				  (30)
 *			/  \				  /	 \
 *		 (10) (100)			   (10)	(50)
 *		 /	\	  		=>	   /	/  \
 *	   (5)  (30)			 (5) (40) (100)
 *			   \
 *			  (40)
 */
void test_doubleRightRotate_given_6_elements_should_rotate_to_balance_tree() {
	Node Node40 = {.data=40, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node5 = {.data=5, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node30 = {.data=30, .balance=1, .leftChild=NULL, .rightChild=&Node40};
	Node Node10 = {.data=10, .balance=1, .leftChild=&Node5, .rightChild=&Node30};
	Node Node100 = {.data=100, .balance=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .balance=-2, .leftChild=&Node10, .rightChild=&Node100};

	Node *root;
	
	root = doubleRightRotate(&Node50);
	TEST_ASSERT_EQUAL_PTR(&Node30, root);
	TEST_ASSERT_EQUAL_PTR(&Node10, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node5, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node40, root->rightChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node100, root->rightChild->rightChild);

	TEST_ASSERT_NULL(Node10.rightChild);
	TEST_ASSERT_NULL(Node5.leftChild);
	TEST_ASSERT_NULL(Node5.rightChild);
	TEST_ASSERT_NULL(Node40.leftChild);
	TEST_ASSERT_NULL(Node40.rightChild);
	TEST_ASSERT_NULL(Node100.leftChild);
	TEST_ASSERT_NULL(Node100.rightChild);
	
	TEST_ASSERT_EQUAL(0, Node30.balance);
	TEST_ASSERT_EQUAL(-1, Node10.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(0, Node5.balance);
	TEST_ASSERT_EQUAL(0, Node40.balance);
	TEST_ASSERT_EQUAL(0, Node100.balance);
}


