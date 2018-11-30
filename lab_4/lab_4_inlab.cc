//Sammy Balusu
//Thomas Chin

#include <iostream>
#include <cstdlib>
#include <stack>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

template <typename T>
struct Node 
{
	T value;
	Node<T> *left, *right;
	int size;
	Node() : left(NULL), right(NULL) {}
	Node(const T& x) : value(x), left(NULL), right(NULL) {}
};

template <typename T>
class BST 
{
  Node<T>* root;
  
  Node<T>** searchNode(const T& x) 
  {
  	Node<T>** p = &root;
	while (*p != NULL) 
	 {
  		if ((*p)->value < x)
  			p = &((*p)->right);
  		else if (x < (*p)->value)
  			p = &((*p)->left);
  		else
  		    return p;  // Element found in the tree, return it
  	}
  	return p; // Element not found in the tree, return a pointer to where it is supposed to be
  }
public:
  BST() : root(NULL) {}
  ~BST() 
	{
		// Delete all nodes in the tree
		stack<Node<T>*> toDelete;
		toDelete.push(root);
		while (!toDelete.empty()) 
		{
			Node<T>* node = toDelete.top();
			toDelete.pop();
			if (node != NULL) {
			delete node;
			toDelete.push(node->left);
			toDelete.push(node->right);
			}
		}
	}
  
	bool insert(const T& x) 
	{
		Node<T>** p = searchNode(x);
		bool finish = false;
		if (*p != NULL)
			return false; 

		// Element found in the tree but we do not currently support duplicate values
		// The pointer falled off the tree, the new value should be inserted at
		// the current pointer position
		
		(*p) = new Node<T>();
		(*p)->value = x;
		
		p = &root;
		while (!finish) 
		{
			if ((*p)->value < x)
			{
				(*p)->size = (*p)->size + 1;
				p = &((*p)->right);
			}
			else 
				if ((*p)->value > x)
				{
					(*p)->size = (*p)->size + 1;
					p = &((*p)->left);
				}
				else
					if((*p)->value == x)
					{
						(*p)->size = (*p)->size + 1;
						finish = true;
					}
		}
	}
  
	bool search(const T& x) 
	{
		Node<T>** p = searchNode(x);
		return *p != NULL;
	}
  
	bool erase(const T& x) 
	{
		Node<T>** p = searchNode(x);
		if (*p == NULL)
			return false; // Element not found in the tree
		// Check the three cases
		if ((*p)->left == NULL && (*p)->right == NULL) {
			// TODO Case 1: Deleting a leaf node
		} else if ((*p)->left == NULL || (*p)->right == NULL) {
			// TODO Case 2: Deleting a node with one child
		} else {
			// TODO Case 3: Deleting a node with two children
		}
		return false;
	}
  
	bool empty() 
	{
		return root == NULL;
	}
	
	int findRank(Node<T>* node, Node<T>* toFind, int rank)
	{
		if(toFind->value < node->value)
		{
			return findRank(node->left, toFind, rank);
			if(toFind->value > node->value)
				rank = node->size;
		}
		else
		  if(toFind->value > node->value)
		  {
			  rank = findRank(node->right, toFind, rank);
			  if(toFind->value > node->value)
				  rank = node->size;
		  }
		  else
		  {
			rank = node->size;
			return rank;
		  }
			  
		return rank;
	}


	/***********TEST FUNCTIONS*****************/
	void testFindSize()
	{
		cout << "Size of 3 (should be 7) = " << root->size << endl;
		cout << "Size of 5 (should be 3) = " << (root->right)->size << endl;
		cout << "Size of 2 (should be 3) = " << (root->left)->size << endl;	
		cout << "Size of 4 (should be 1) = " << ((root->right)->right)->size << endl;
		
		cout << endl;

		return;
	}

	void testFindRank()
	{
		int rank = 0;

		cout << "Rank of 3 (should be 7) = " << findRank(root, root, rank) << endl;
		cout << "Rank of 5 (should be 7) = " << findRank(root, root->right, rank) << endl;
		cout << "Rank of 2 (should be 3) = " << findRank(root, (root->left)->right, rank) << endl;
		cout << "Rank of 7 (should be 7) = " << findRank(root, (root->right)->right, rank) << endl;
		cout << "Rank of 1 (should be 3) = " << findRank(root, root->left, rank) << endl;
		cout << "Rank of 0 (should be 1) = " << findRank(root, (root->left)->left, rank) << endl;
		cout << "Rank of 4 (should be 1) = " << findRank(root, (root->left)->right, rank) << endl;
	}

};


int main(){
	// Simple tests for the binary search tree
	BST<int> bst;
	// Test insert and search
	bst.insert(3);		/*			(3)			*/
	bst.insert(1);		/*		  /	 	\		*/
	bst.insert(5);		/*		(1)		 (5)	*/
	bst.insert(2);		/*	   /   \	/   \	*/
	bst.insert(4);		/*   (0)   (2)(4)	(7)	*/
	bst.insert(7);		/*						*/
	bst.insert(0);		/*						*/

	//test size function
	bst.testFindSize();

	//test rank function
	bst.testFindRank();
	
	return 0;

}
