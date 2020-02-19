/****************************************************************************
Programmer : Branden Hidalgo
ZID	   : Z1663752
Section	   : 1
Assignment : 5
****************************************************************************/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "assignment5.h"
using namespace std;

const int MAX_SIZE = 40;
const int MAX_COUNT = 40;
const int WIDTH = 5;
const int ROW_SIZE = 8;

int mcount = 0;
int rcount = 0;

void display(int d) {
    if ( mcount < MAX_COUNT ) {
        cout << setw(WIDTH) << d;
        mcount++;
        rcount++;
        if ( rcount == ROW_SIZE ) {
            cout << endl;
            rcount = 0;
        }
    }
}
/****************************************************************************
Function:  bintree()
Arguments: N/A
Returns:   N/A
Purpose:   Creates a binTree object with a root initalized at nullptr
Notes:     Constructor for the binTree class
****************************************************************************/
binTree::binTree()
{
   root = nullptr;
}

/****************************************************************************
Function:  int height() const
Arguments: N/A
Returns:   Integer
Purpose:   A constant function which is used for checking the height of a tree
Notes:     Public version. Makes a recursive call if a tree is not empty.
           Otherwise, returns -1.
*****************************************************************************/
int binTree::height() const
{  if(root != nullptr)
     return height(root);
   return -1;
}

/*****************************************************************************
Function:  int height(Node*) const
Arguments: A Node pointer
Returns:   Integer
Purpose:   Constant method used to check the height of a tree
Notes:	   Private version. If tree is not empty, returns the highest branch of
           the tree. Otherwise, returns -1.
******************************************************************************/
int binTree::height(Node* n) const
{
   if(n != nullptr)
   {
     int heightl, heightr;
     heightl = 1 + height(n->left);
     heightr = 1 + height(n->right);
     if(heightl > heightr)
       return heightl;

     return heightr;
   }
 return -1;
}

/*****************************************************************************
Function:  unsigned size() const
Arguments: N/A
Returns:   Unsigneed integer
Purpose:   Constant function that returns the total number of nodes in a tree
Note:	   Public version. Makes a recursive call.
*****************************************************************************/
unsigned binTree::size() const
{
   return size(root);
}

/*****************************************************************************
Function:  unsigned size(Node*) const
Arguments: N/A
Returns:   Unsigned Integer
Purpose:   A constant function that returnst the total number of nodes in a tree.
Note:	   Private version. If tree is not empty, makes recursive calls.
           Otherwise, returns 0
*****************************************************************************/
unsigned binTree::size(Node* n) const
{
   if(n != nullptr)
   {
      return 1 + size(n->left) + size(n->right);
   }
return 0;
}
/****************************************************************************
Function:  void insert(int)
Arguments: Integer
Returns:   N/A
Purpose:   Inserts a node into the tree
Notes:     Public version. Calls the private version
***************************************************************************/
void binTree::insert(int x)
{
   insert(root, x);
}

/***************************************************************************
Function:  void insert(Node*&, int)
Arguments: Node pointer and an integer
Returns:   N/A
Purpose:   Insert a node into a tree
Notes:     Private version. If subtree is empty, insert node with value at root.
           Otherwise, insert the node in the shorter branch.
****************************************************************************/
void binTree::insert(Node*& r, int x)
{
   if(r == nullptr)
   {
     r = new Node;
     r->val = x;
     r->left = nullptr;
     r->right = nullptr;
   }
   else
   {
     int heightl = height(r->left);
     int heightr = height(r->right);
     if(heightr < heightl)
     {
      insert(r->right, x);
     }
     else
      insert(r->left, x);
   }
}

/****************************************************************************
Function:  void inorder(void(*)(int))
Arguments: Function pointer
Returns:   N/A
Purpose:   Traverse a tree in the inorder manner
Notes:     Public version. Calls the private version
*****************************************************************************/
void binTree::inorder(void(*p)(int))
{
 inorder(root, p);
}

/****************************************************************************
Function:  void inorder(Node*, void(*)(int))
Arguments: Node pointer and function pointer
Returns:   N/A
Purpose:   Traverse a tree in the inorder manner
Notes:     Private version. Makes a recursive call.
****************************************************************************/
void binTree::inorder(Node* r, void(*p)(int))
{
 if(r != nullptr)
 {
  inorder(r->left, p);
  p(r->val);
  inorder(r->right, p);
 }
}

/****************************************************************************
Function:  void preorder(void(*)(int))
Arguments: Function pointer
Returns:   N/A
Purpose:   Traverse a tree in preorder manner
Notes:     Public version. Calls Private version.
*****************************************************************************/
void binTree::preorder(void(*p)(int))
{
 preorder(root, p);
}

/*****************************************************************************
Function:  void preorder(Node*, voide(*)(int))
Arguments: Node pointer, function pointer
Returns:   N/A
Purpose:   Traverse a tree in preorder manner
Notes:     Private version. Makes recursion call.
*****************************************************************************/
void binTree::preorder(Node* r, void(*p)(int))
{
 if(r != nullptr)
 {
  p(r->val);
  preorder(r->left, p);
  preorder(r->right, p);
 }
}

/****************************************************************************
Function:  void postorder(void(*)(int))
Arguments: Function pointer
Returns:   N/A
Purpose:   Travers a tree in postorder manner
Notes:     Public version. Calls private version.
****************************************************************************/
void binTree::postorder(void(*p)(int))
{
 postorder(root, p);
}
/****************************************************************************
Function:  void postorder(Node* r, void(*)(int))
Arguments: Node pointer and function pointer
Returns:   N/A
Purpose:   Traverse a tree in postorder manner
Notes:     Private version. Makes recursion call.
****************************************************************************/
void binTree::postorder(Node* r, void(*p)(int))
{
 if(r != nullptr)
 {
  postorder(r->left, p);
  postorder(r->right, p);
  p(r->val);
 }
}

//#define BINTREE_MAIN
#ifdef BINTREE_MAIN
int main() {
    vector<int> v(MAX_SIZE);
    for (int i=1; i<MAX_SIZE; i++)
        v[i] = i;
    random_shuffle( v.begin(), v.end() );

    binTree bt;
    vector<int>::iterator it;
    for (it=v.begin(); it!=v.end(); it++)
        bt.insert( *it );

    cout << "Height: " << bt.height() << endl;
    cout << "Size: " << bt.size() << endl;
    cout << "In order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.inorder( display );
    cout << "\n\nPre order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.preorder( display );
    cout << "\n\nPost order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.postorder( display );

    cout << endl;
    return 0;
}

#endif
