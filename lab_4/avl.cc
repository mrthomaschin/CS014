#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

/// This macro makes it more convenient to retrieve the height of an empty subtree
#define HEIGHT(n) (((n) == NULL)? -1 : ((n)->height))

template <typename T>
struct Node {
	T value;
	int height;
	Node<T> *left, *right;
	Node() : left(NULL), right(NULL), height(0) {}
	Node(const T& x) : value(x), left(NULL), right(NULL), height(0) {}
	
	/// Update the height of the subtree rooted at this node assuming that the
	/// two subtrees have the correct height
	void updateHeight() {
		height = max(HEIGHT(left), HEIGHT(right)) + 1;
	}
	
	/// Check if this node is balanced according to the AVL tree condition
	bool balanced() {
		return abs(HEIGHT(left) - HEIGHT(right)) <= 1;
	}
	
	// Perform a single rotation at the current node and return the new root after rotation
	Node* singleLeftRotation() {
		// TODO Update the links as mandated by this rotation
		Node<T>* newRoot = this->right;
		Node<T>* temp = newRoot->left;
		
		newRoot->left = this;
		this->right = temp;
		
		// TODO Do not forget to udpate the tree height for the updated subtrees
		this->updateHeight();
		newRoot->updateHeight();
		
		// TODO Make sure to return the updated root after rotation

		return newRoot;
	}
	
	// Perform a single rotation at the current node and return the new root after rotation
	Node* singleRightRotation() {
		// TODO Update the links as mandated by this rotation
		Node<T>* newRoot = this->left;
		Node<T>* temp = newRoot->right;
		
		newRoot->right = this;
		this->left = temp;
		
		// TODO Do not forget to udpate the tree height for the updated subtrees
		this->updateHeight();
		newRoot->updateHeight();
		
		// TODO Make sure to return the updated root after rotation

		return newRoot;
	}
	
	// Perform a double rotation at the current node and return the new root after rotation
	Node* doubleLeftRightRotation() {
		// TODO Update the links as mandated by this rotation
		// TODO Do not forget to udpate the tree height for the updated subtrees
		// TODO Make sure to return the updated root after rotation

		this->left = (this->left)->singleLeftRotation();

		return this->singleRightRotation();
	}
	
	// Perform a double rotation at the current node and return the new root after rotation
	Node* doubleRightLeftRotation() {
		// TODO Update the links as mandated by this rotation
		// TODO Do not forget to udpate the tree height for the updated subtrees
		// TODO Make sure to return the updated root after rotation

		this->right = (this->right)->singleRightRotation();
		
		return this->singleLeftRotation();
	}
};

// The following few lines are to override the << operator
#include "print_ascii.cc"
template <typename T>
class AVL;

template <typename T>
std::ostream& operator<< (std::ostream& out, const AVL<T>& v);

template <typename T>
class AVL {
  Node<T>* root;
  
  vector<Node<T>*> searchNode(const T& x) {
  	vector<Node<T>*> path;
  	Node<T>* p = root;
  	while (p != NULL) {
  		path.push_back(p);
  		if (p->value < x)
  			p = p->right;
  		else if (x < p->value)
  			p = p->left;
  		else
  		    return path;  // Element found in the tree, return the full path from the root to the node
  	}
  	return path; // Element not found in the tree, return the path to where the node is supposed to be
  }
public:
  AVL() : root(NULL) {}
  ~AVL() {
  	// Delete all nodes in the tree
  	stack<Node<T>*> toDelete;
  	toDelete.push(root);
  	while (!toDelete.empty()) {
  		Node<T>* node = toDelete.top();
  		toDelete.pop();
  		if (node != NULL) {
  		  delete node;
  		  toDelete.push(node->left);
  		  toDelete.push(node->right);
  		}
  	}
  }
  
  bool insert(const T& x) {
  	vector<Node<T>*> p = searchNode(x);
  	if (p.empty()) {
  		// Inserting at the root
  		root = new Node<T>(x);
  		// No need to check the balance after inserting one node
  		return true;
  	} else {
  		// Inserting at a non-root node
  		Node<T>* newNode = new Node<T>(x);
  		Node<T>* parent = p.back();
  		if (parent->value < x)
  			parent->right = newNode;
  		else
  			parent->left = newNode;
  		p.push_back(newNode);
  		// Now we need to update the tree height and check the balance
  		for (int i = p.size() - 1; i >= 0; i--) {
			p[i]->updateHeight();
			if (!p[i]->balanced()) {
  				// Balance the tree after insertion
  				// TODO Perform the correct rotation to balance p[i]
  				// TODO Do not forget to update the tree link pointing to p[i] after the rotation is done
  				// TODO Do not forget to update the height of the tree nodes after the rotation
				  //      to ensure that future insert operations will work correctly
					Node<T>* temp = p[i];
					int total = HEIGHT(temp->left) - HEIGHT(temp->right);

					if(total > 1 && x < (temp->left)->value)
					{
						if(temp == root)
						{
							root = temp->singleRightRotation();

							return true;
						}
						else
						{
							(p.at(i - 1))->left = temp->singleRightRotation();
							continue;
						}
					}

					if(total < -1 && x > (temp->right)->value)
					{
						if(temp == root)
						{
							root = temp->singleLeftRotation();

							return true;
						}
						else
						{
							(p.at(i - 1))->right = temp->singleLeftRotation();
							return true;
						}
					}

					if(total > 1 && x > (temp->left)->value)
					{
						if(temp == root)
						{
							root = temp->doubleLeftRightRotation();

							return true;
						}
						else
						{
							(p.at(i - 1))->left = temp->doubleLeftRightRotation();
							return true;
						}
					}

					if(total < -1 && x < (temp->right)->value)
					{
						if(temp == root)
						{
							root = temp->doubleRightLeftRotation();

							return true;
						}
						else
						{
							(p.at(i - 1))->right = temp->doubleRightLeftRotation();
							return true;
						}
					}

					else
					{
						return false;
					}

  			}
  		}
  	}
  }
  
  bool search(const T& x) {
  	vector<Node<T>*> p = searchNode(x);
  	return !p.empty() && p.back()->value == x;
  }
  
  /// Return true if the tree is empty
  bool empty() {
  	return root == NULL;
  }
  
  /// Check if all the nodes in the tree are balanced according to the AVL balance condition
  bool balanced() {
  	stack<Node<T>*> toTest;
  	toTest.push(root);
  	while (!toTest.empty()) {
  		Node<T>* n = toTest.top();
  		toTest.pop();
  		if (n != NULL) {
	  		if (!n->balanced())
	  			return false;
	  		toTest.push(n->left);
	  		toTest.push(n->right);
  		}
  	}
  	return true;
  }
  
  /// Make the << function a friend function to ensure it has access to root
  friend std::ostream& operator<< <> (std::ostream& out, const AVL<T>& v);
};

template <typename T>
std::ostream& operator<< (std::ostream& out, const AVL<T>& v) {
	print_ascii_tree(out, v.root);
	return out;
}

int main() {
	// HINT: Use cout << avl to print the tree after each insertion or rotate.
	//       It might make it more convenient to debug and understand what is going on.
	// Simple test for the four cases after insertion
	AVL<int> avl;
	avl.insert(10);
	avl.insert(9);
	avl.insert(7); // A single right rotation should happen here
	EXPECT_TRUE(avl.balanced());
	avl.insert(14);
	avl.insert(18);
	EXPECT_TRUE(avl.balanced());
	avl.insert(11); // A double rotation should happen here
	EXPECT_TRUE(avl.balanced());
	avl.insert(8);
	EXPECT_TRUE(avl.balanced());

	// A good way to test an AVL tree is to create a worst-case scenario by
	// inserting items in the sorted order and make sure that the tree is
	// balanced after each insertion
	AVL<int> seq_avl;
	for (int i = 1; i <= 20; i++) {
		seq_avl.insert(i);
		EXPECT_TRUE(seq_avl.balanced());
	}
	
	// Print the final tree
	cout << seq_avl << endl;
	return 0;
}
