#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <stack>
#include "helper.hh"

using namespace std;

template <typename T>
vector<T> preorderTraversalNoRecursion(Node<T>* root) 
{
  vector<T> preorder;
  stack<Node<T>*> treeStack;
  bool cont = true;

  if (root == NULL)
    return preorder;

  /*
  // 1. root
  preorder.push_back(root->value);

  // 2. Preorder left
  vector<T> preorderLeft = preorderTraversalNoRecursion(root->left);
  preorder.insert(preorder.end(), preorderLeft.begin(), preorderLeft.end());

  // 3. Preorder right
  vector<T> preorderRight = preorderTraversalNoRecursion(root->right);
  preorder.insert(preorder.end(), preorderRight.begin(), preorderRight.end());

  return preorder;*/

  treeStack.push(root);

  while(treeStack.empty() == false)
  {
    Node<T>* node = treeStack.top(); //reset root
    preorder.push_back(node->value);  //print top value
    treeStack.pop();

    if(node->right) //push right (goes last)
      treeStack.push(node->right);
    if(node->left)
      treeStack.push(node->left); //push left

  }

  return preorder;

}

template <typename T>
vector<T> inorderTraversalNoRecursion(Node<T>* root) 
{
  vector<T> inorder;
  stack<Node<T>*> treeStack;
  Node<T>* curr = root;
  bool cont = true;
  
  if (root == NULL)
    return inorder;

  if(root->left == NULL && root->right == NULL)
  {
    inorder.push_back(root->value);
    return inorder;
  }
  
  /* // 1. Inorder left
  vector<T> inorderLeft = inorderTraversalNoRecursion(root->left);
  inorder.insert(inorder.end(), inorderLeft.begin(), inorderLeft.end());

  // 2. root
  inorder.push_back(root->value);

  // 3. Inorder right
  vector<T> inorderRight = inorderTraversalNoRecursion(root->right);
  inorder.insert(inorder.end(), inorderRight.begin(), inorderRight.end());

  return inorder;*/ 

  while(cont)
  {
    
    if(curr != NULL)  //Traverse down left side of tree
    {
      treeStack.push(curr);
      curr = curr->left;
    }
    else
    {
      if(treeStack.empty() == false) //goes up, stores values, moves to the right IF THERE IS ANY
      {
        curr = treeStack.top();
        treeStack.pop();
        inorder.push_back(curr->value);
        curr = curr->right;
      }
      else  //stops loops
        cont = false;
    }
  } 

  return inorder;
}

void testPreorder() 
{
  Node<int>* root = buildTree(vector<int>({1}), vector<int>({1}));
  vector<int> preorder = preorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1}), preorder);
  delete(root);
  
  root = buildTree(vector<int>({10, 8, 3, 5, 2, 7}), vector<int>({3, 8, 5, 10, 7, 2}));
  preorder = preorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({10, 8, 3, 5, 2, 7}), preorder);
  delete(root);

  root = buildTree(vector<int>({1, 2, 3, 4, 5}), vector<int>({1, 4, 3, 2, 5}));
  preorder = preorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1, 2, 3, 4, 5}), preorder);
  delete(root);
}


void testInorder() {
  Node<int>* root = buildTree(vector<int>({1}), vector<int>({1}));
  vector<int> inorder = inorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1}), inorder);
  delete(root);

  root = buildTree(vector<int>({10, 8, 3, 5, 2, 7}), vector<int>({3, 8, 5, 10, 7, 2}));
  inorder = inorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({3, 8, 5, 10, 7, 2}), inorder);
  delete(root);

  root = buildTree(vector<int>({1, 2, 3, 4, 5}), vector<int>({1, 4, 3, 2, 5}));
  inorder = inorderTraversalNoRecursion(root);
  ASSERT_EQ(vector<int>({1, 4, 3, 2, 5}), inorder);
  delete(root);

}


int main() {
  testBuildTree();
  testPreorder();
  testInorder();
  
  Node<int>* root = buildTree(vector<int>({10, 8, 3, 5, 2, 7}), vector<int>({3, 8, 5, 10, 7, 2}));

  vector<int> preorder = preorderTraversalNoRecursion(root);
  vector<int> inorder = inorderTraversalNoRecursion(root);

  cout << "Preorder: " << preorder << endl
       << "Inorder: " << inorder << endl;
  cout << "Finished succesfully!" << endl;
}

