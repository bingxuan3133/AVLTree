#include "unity.h"
#include "Rotation.h"
#include "getHeight.h"
#include "AVL.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_avlAdd_balance() {
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
	TEST_ASSERT_EQUAL(1, Node120.balance);
	TEST_ASSERT_EQUAL(0, Node150.balance);
	TEST_ASSERT_EQUAL(0, Node50.balance);
	TEST_ASSERT_EQUAL(0, Node100.balance);
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
 *		 \					  50
 *		  50		=>		 /	\
 *		  	\				1	100
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
 *		1	100
 *			/
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
 *		1	100
 *			/ \
 *		  75  150
 */
void xtest_avlAdd_1_50_100_75_150() {
printf("niama\n");
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
	
	// TEST_ASSERT_EQUAL(0, Node1.balance);
	// TEST_ASSERT_EQUAL(1, Node50.balance);
	// TEST_ASSERT_EQUAL(0, Node100.balance);
	// TEST_ASSERT_EQUAL(0, Node75.balance);
	// TEST_ASSERT_EQUAL(0, Node150.balance);
}




