#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
using namespace std;

Profiler p("Ordered Statistics");
#define MAX 10000

//int height; //how many nodes are just under one node

int OP_SELECT = 0, OP_DELETE = 0, OP_BUILD = 0;

struct node
{
	int key;
	int size; // the size of the subtree which has this node as root
	struct node* left;
	struct node* right;
	struct node*parent;
};

struct node* newNode(int key)
{
	node *n = (struct node*)malloc(sizeof(struct node));
	if (n) {
		OP_BUILD++;
		n->key = key;
		n->size = NULL;
		n->left = NULL;
		n->right = NULL;
		n->parent = NULL;
	}
	return n;
}

node* build_tree(int *array, int first, int last) {

	int middle;

	if (first <= last) {
		//op.count(4);
		// we take the middle from the initial array
		middle = (first + last) / 2;

		// we create a new node
		// then its children are the middles from the the two halves of the array
		node* root = newNode(array[middle]);
		root->left = build_tree(array, first, middle - 1);
		//height = 0; //
		root->right = build_tree(array, middle + 1, last);
		//height++; 

		// tie these children with their parent
		//if (root->left)
			//root->left->parent =root;
		//if (root->right)
			//root->right->parent = root;

		// we calculate the size for this node

		if (root->left == NULL && root->right == NULL)
			root->size = 1;
		else
			if (root->left && root->right)
			{
				OP_BUILD++;
				root->size = root->left->size + root->right->size + 1; //it has 2 children
			}
			else if(root->left==NULL)
			{
				root->size = root->right->size + 1;
				
			}
			else
			{
				root->size = root->left->size + 1;
			}
		return root;
	}
	else
		return NULL;

}
void prettyPrint(node *root, int recLevel) //! root, index, length,reccurence level
{
	if (root == NULL)
	{
		recLevel--; //! reached leaf, must decrement recurence level
		return;
	}
	recLevel++; //! otherwise increment it
	prettyPrint(root->right, recLevel); //! keep going right in the tree
	int j = 0;

	//! print spaces for the appropriate recurence level
	for (j = 0; j < recLevel - 1; j++)
	{
		printf("     ");

	}
	//! then print value

	printf("%d|%d", root->key, root->size);

	//! print  a new line
	printf("\n");


	prettyPrint(root->left, recLevel); //! keep going left in the tree
}

node* os_select(node* node, int i) {

	int rank;
	//OP_SELECT++; 
	//firstly we compute the rank of the given node, with the information on its left subtree
	if (node->left != NULL) {
		OP_SELECT++;
		rank = node->left->size + 1;
	}
	else
		rank = 1; //rank shows thatthe node is a leaf
	OP_SELECT++;
	if (i == rank)
		return node; //rank shows that the ith smallest is found
	else
	{
		OP_SELECT++;
		if (i < rank)
			return os_select(node->left, i);
		else

			return os_select(node->right, i - rank);
	}
		
}

//minimum from the tree
node* minValueNode(node* n)
{
	struct node* current = n;


	while (current->left != NULL)
		current = current->left;

	return current;
}


node* os_delete(node *root, int val, int size)
{
	OP_DELETE++;
	//base case
	if (root == NULL)
	{
		//OP_DELETE++;
		return root;
	}
	
	OP_DELETE++;
	// if the value to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (val< root->key)
	{
		//OP_DELETE += 2;
		root->left = os_delete(root->left, val, size);
	}
	
	// If the value to be deleted is greater than the root's key, 
   // then it lies in right subtree 
	else if (val> root->key)
	{
		OP_DELETE += 1;
		root->right = os_delete(root->right, val, size);
	}

	// if value is same as root's key, then this is the node 
	// to be deleted 
	else
	{
		if (root->left == NULL)
		{
			//OP_DELETE += 2;
			struct node *aux = root->right;
			free(root);
			return aux;
		}
		else if (root->right == NULL)
		{
			//OP_DELETE += 2;
			struct node *aux = root->left;
			free(root);
			return aux;
		}
		
		// node with two children: Get the inorder successor (smallest 
	   // in the right subtree) 
		OP_DELETE += 1;
		struct node *aux = minValueNode(root->right);
		// Copy the inorder successor's content to this node 
		root->key = aux->key;
		// Delete the inorder successor 
		root->right = os_delete(root->right, aux->key, size);

	}
	
	root->size = 1;
	
    if (root->left != NULL)
	{

		//OP_DELETE += 2;  
		root->size += root->left->size;
	}
	if (root->right != NULL)
	{
	
		//OP_DELETE += 2;
		root->size += root->right->size;
	}
	return root;
}

void demo() {
	
	int n = 11;
	int a[11] = { 1,2,3,4,5,6,7,8,9,10,11 };

	struct node *root = build_tree(a, 0, n - 1);
	prettyPrint(root, 0);
	cout << endl;
	
	node *selection1 = os_select(root, 2);
	cout << endl << selection1->key << endl;
	cout << endl;
    root = os_delete(root, selection1->key, n);
	prettyPrint(root, 0);

	node *selection2 = os_select(root, 5);
	cout << endl << selection2->key << endl;
	cout << endl;
    root = os_delete(root, selection2->key, n);
	prettyPrint(root, 0);

	node *selection3 = os_select(root, 7);
	cout << endl << selection3->key << endl;
	cout << endl;
    root = os_delete(root, selection3->key, n);
	prettyPrint(root, 0);


}

void average_case() {

	int a[MAX];
	p.createGroup("OS_OPERATIONS", "TOTAL_OPERATIONS", "SELECT_OPERATIONS", "DELETE_OPERATIONS");
	node *nodeToBeDeleted;
	for (int n = 100; n <= MAX; n += 100)
	{
		cout << n << '\n';
		for (int rep = 0; rep < 5; rep++)
		{
			FillRandomArray(a, n, 10, 50000, true, 1);
			struct node *root = build_tree(a, 0, n - 1);
			for (int rem = n; rem >= 1; rem--) //rem=no of elements
			{
				int x = rand() % rem + 1;
				nodeToBeDeleted = os_select(root, x);
				root = os_delete(root, nodeToBeDeleted->key, n);

			}
		}

		OP_SELECT /= 5;
		OP_DELETE /= 5;
		OP_BUILD /= 5;
		p.countOperation("SELECT_OPERATIONS", n, OP_SELECT);
		p.countOperation("DELETE_OPERATIONS", n, OP_DELETE);
		p.countOperation("TOTAL_OPERATIONS", n, OP_SELECT + OP_DELETE + OP_BUILD);

		OP_SELECT = 0;
		OP_DELETE = 0;
		OP_BUILD = 0;

	}

	p.showReport();
}

int main() {
	demo();  
	//average_case();

	getchar();
	return 0;
	
}


