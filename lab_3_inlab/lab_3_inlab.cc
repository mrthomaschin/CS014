#include <iostream>
#include <vector>
#include "helper.hh"

using namespace std;

template <typename T>
Node<T>* nextInorder(Node<T>* root, Node<T>* toFind) 
{
  if(toFind == root)                      //root condition
  {
    toFind = toFind->right;
    while(toFind->left)
    {
      toFind = toFind->left;
    }

    return toFind;
  }
  else
    if(toFind->right)   //parent, has left child
    {
      return toFind->right;
    }
    else
      if(toFind == (toFind->parent)->left)  //left child
      {
        return toFind->parent;
      } 
      else
        if(toFind == (toFind->parent)->right) //right child
        {
          while(toFind != root)
          {
            if((toFind->parent)->parent && (toFind->parent) == ((toFind->parent)->parent)->left)  //If parent's parent moves right, not a special case
              return (toFind->parent)->parent;
            else
              if(toFind== root->left)   //If the ending node is to the left of the root, result is root
                return root; 

            toFind = toFind->parent;  //move pointe rup
          }

        return NULL;  //If while ends, the original node is to the right of the root, therefore is NULL
      }
} 

int main() 
{

  Node<int>* root = buildTree(vector<int>({10, 8, 3, 5, 2, 7}), vector<int>({3, 8, 5, 10, 7, 2}));
  Node<int>* toFind = (root->left);

  Node<int>* result = nextInorder(root, toFind);

  if(result)
    cout << "Next(" << toFind->value << ") = " << result->value << endl;  
  else
    cout << "Next(" << toFind->value << ") = NULL" << endl;  

  return 0;
}

