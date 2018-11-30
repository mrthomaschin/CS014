using namespace std;

template <typename T>
struct Node {
  T value;
  Node<T>* parent;
  Node<T>* left;
  Node<T>* right;
  
  Node(const T& val) {
    value = val; 
    left = NULL; 
    right = NULL;
    parent = NULL;
  }
  
  ~Node() {
    delete(left);
    delete(right);
    delete(parent);
  }
};


template <typename T>
Node<T>* construct(const vector<T>& preorder, int preStart, int preEnd, const vector<T>& inorder, int inStart, int inEnd, Node<T>* myParent){
  if(preStart>preEnd||inStart>inEnd){
    return NULL;
  }
  T val = preorder[preStart];
  Node<T>* p = new Node<T>(val);

  p->parent = myParent;

  //find parent element index from inorder
  int k=0;
  for(int i=0; i<inorder.size(); i++){
    if(val == inorder[i]){
      k=i;
      break;
    }
  }

  p->left = construct(preorder, preStart+1, preStart+(k-inStart), inorder, inStart, k-1, p);
  p->right= construct(preorder, preStart+(k-inStart)+1, preEnd, inorder, k+1 , inEnd, p);
  return p;
}

// Code courtesy of https://www.programcreek.com/2014/06/leetcode-construct-binary-tree-from-preorder-and-inorder-traversal-java/
template <typename T>
Node<T>* buildTree(const vector<T>& preorder, const vector<T>& inorder) {
  int preStart = 0;
  int preEnd = preorder.size()-1;
  int inStart = 0;
  int inEnd = inorder.size()-1;
  Node<T>* p = NULL;
  return construct(preorder, preStart, preEnd, inorder, inStart, inEnd, p);
}
