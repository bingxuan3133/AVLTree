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

/**
 *		(1)
 */
void test_getHeight_should_return_1_when_length_of_the_tree_is_1() {
	Node Node1 = {.data=1, .rank=0, .leftChild=NULL, .rightChild=NULL};
	
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
	Node Node3 = {.data=3, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .rank=1, .leftChild=NULL, .rightChild=&Node3};
	Node Node1 = {.data=1, .rank=2, .leftChild=NULL, .rightChild=&Node2};
	
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
	Node Node1 = {.data=1, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node4 = {.data=4, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .rank=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node3 = {.data=3, .rank=-1, .leftChild=&Node2, .rightChild=&Node4};
	
	_getHeight_ExpectAndReturn(&Node2, 2);
	_getHeight_ExpectAndReturn(&Node4, 1);
	
	int result = getHeight(&Node3);
	
	TEST_ASSERT_EQUAL(3, result);
}


/**
 *		(1)			  (2)
 *		  \			  / \
 *		  (2)	=>	(1)	(3)
 *			\
 *			(3)
 */
void test_leftRotate_given_3_elements_should_rotate_to_balance_tree() {
	Node Node3 = {.data=3, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .rank=1, .leftChild=NULL, .rightChild=&Node3};
	Node Node1 = {.data=1, .rank=2, .leftChild=NULL, .rightChild=&Node2};
	
	Node *root;
	
	root = leftRotate(&Node1);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.rank);
	TEST_ASSERT_EQUAL(0, Node1.rank);
	TEST_ASSERT_EQUAL(0, Node3.rank);
}

/**
 *			(3)		  (2)
 *		  	/	  	  / \
 *		  (2)	=>	(1)	(3)
 *		  /
 *		(1)
 */
void test_rightRotate_given_3_elements_should_rotate_to_balance_tree() {
	Node Node1 = {.data=1, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node2 = {.data=2, .rank=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node3 = {.data=3, .rank=-2, .leftChild=&Node2, .rightChild=NULL};
	
	Node *root;
	
	root = rightRotate(&Node3);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.rank);
	TEST_ASSERT_EQUAL(0, Node1.rank);
	TEST_ASSERT_EQUAL(0, Node3.rank);
}

/**
 *		  (1)	  	  (2)
 *		  	\		  / \
 *			(3)	=>	(1)	(3)
 *		  	/
 *		  (2)
 */
void test_doubleLeftRotate_given_3_elements_should_rotate_to_balance_tree() {
	Node Node2 = {.data=2, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node3 = {.data=3, .rank=-1, .leftChild=&Node2, .rightChild=NULL};
	Node Node1 = {.data=1, .rank=2, .leftChild=NULL, .rightChild=&Node3};
	
	Node *root;
	
	root = doubleLeftRotate(&Node1);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.rank);
	TEST_ASSERT_EQUAL(0, Node1.rank);
	TEST_ASSERT_EQUAL(0, Node3.rank);
}

/**
 *		  (3)		  (2)
 *		  /			  / \
 *		(1)		=>	(1)	(3)
 *		  \
 *		  (2)
 */
void test_doubleRightRotate_given_3_elements_should_rotate_to_balance_tree() {
	Node Node2 = {.data=2, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node1 = {.data=1, .rank=1, .leftChild=NULL, .rightChild=&Node2};
	Node Node3 = {.data=3, .rank=-2, .leftChild=&Node1, .rightChild=NULL};
	
	Node *root;
	
	root = doubleRightRotate(&Node3);
	TEST_ASSERT_EQUAL_PTR(&Node2, root);
	TEST_ASSERT_EQUAL_PTR(&Node1, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node3, root->rightChild);
	TEST_ASSERT_NULL(root->leftChild->leftChild);
	TEST_ASSERT_NULL(root->leftChild->rightChild);
	TEST_ASSERT_NULL(root->rightChild->leftChild);
	TEST_ASSERT_NULL(root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node2.rank);
	TEST_ASSERT_EQUAL(0, Node1.rank);
	TEST_ASSERT_EQUAL(0, Node3.rank);
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
void test_leftRotate_given_6_elements_should_rotate_to_balance_tree() {
	Node Node200 = {.data=200, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node150 = {.data=150, .rank=1, .leftChild=NULL, .rightChild=&Node200};
	Node Node70 = {.data=70, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node100 = {.data=100, .rank=1, .leftChild=&Node70, .rightChild=&Node150};
	Node Node10 = {.data=10, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .rank=2, .leftChild=&Node10, .rightChild=&Node100};

	Node *root;
	
	root = leftRotate(&Node50);
	TEST_ASSERT_EQUAL_PTR(&Node100, root);
	TEST_ASSERT_EQUAL_PTR(&Node50, root->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node150, root->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node10, root->leftChild->leftChild);
	TEST_ASSERT_EQUAL_PTR(&Node70, root->leftChild->rightChild);
	TEST_ASSERT_EQUAL_PTR(&Node200, root->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(0, Node100.rank);
	TEST_ASSERT_EQUAL(0, Node50.rank);
	TEST_ASSERT_EQUAL(1, Node150.rank);
	TEST_ASSERT_EQUAL(0, Node10.rank);
	TEST_ASSERT_EQUAL(0, Node70.rank);
	TEST_ASSERT_EQUAL(0, Node200.rank);
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
void test_rightRotate_given_6_elements_should_rotate_to_balance_tree() {
	Node Node1 = {.data=1, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node5 = {.data=5, .rank=-1, .leftChild=&Node1, .rightChild=NULL};
	Node Node30 = {.data=30, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node10 = {.data=10, .rank=-1, .leftChild=&Node5, .rightChild=&Node30};
	Node Node100 = {.data=100, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .rank=-2, .leftChild=&Node10, .rightChild=&Node100};

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
		
	TEST_ASSERT_EQUAL(0, Node10.rank);
	TEST_ASSERT_EQUAL(-1, Node5.rank);
	TEST_ASSERT_EQUAL(0, Node50.rank);
	TEST_ASSERT_EQUAL(0, Node1.rank);
	TEST_ASSERT_EQUAL(0, Node30.rank);
	TEST_ASSERT_EQUAL(0, Node100.rank);
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
	Node Node40 = {.data=40, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node5 = {.data=5, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node30 = {.data=30, .rank=1, .leftChild=NULL, .rightChild=&Node40};
	Node Node10 = {.data=10, .rank=1, .leftChild=&Node5, .rightChild=&Node30};
	Node Node100 = {.data=100, .rank=0, .leftChild=NULL, .rightChild=NULL};
	Node Node50 = {.data=50, .rank=-2, .leftChild=&Node10, .rightChild=&Node100};

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
	
	TEST_ASSERT_EQUAL(0, Node30.rank);
	TEST_ASSERT_EQUAL(-1, Node10.rank);
	TEST_ASSERT_EQUAL(0, Node50.rank);
	TEST_ASSERT_EQUAL(0, Node5.rank);
	TEST_ASSERT_EQUAL(0, Node40.rank);
	TEST_ASSERT_EQUAL(0, Node100.rank);
}



















