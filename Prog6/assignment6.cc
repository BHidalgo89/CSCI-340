#include "assignment5.h"
#include "assignment6.h"
using namespace std;

/***********************************************************************************
Function:  void insert(int x)
Arguments: An integer which is to be inserted into the binary search tree
Returns:   N/A
Purpose:   Allows the insertion of a node into the binary search tree
Notes:     Public version. Calls the private version
***********************************************************************************/
void BST::insert(int x)
{
     insert(root, x);
}

/************************************************************************************
Function:  bool search(int x)
Arguments: An integer, the value of the node being searched for in the tree
Returns:   A boolean value. Returns true if the value is found, false otherwise.
Purpose:   Allows user to search for nodes by value within the tree
Notes:     Public version. Calls private version.
************************************************************************************/
bool BST::search(int x)
{
  return search(root, x);
}

/************************************************************************************
Function:  bool remove(int x)
Arguments: An integer x, the value of the node being removed
Returns:   N/A
Purpose:   Allows the user to remove nodes by value from the tree
Notes:     Public version. Calls private version.
*************************************************************************************/
bool BST::remove(int x)
{
   return  remove(root, x);
}

/***********************************************************************************
Function:  int sumLeaves()
Arguments: N/A
Returns:   An integer value, the sum of the values of the leaf nodes in the tree
Purpose:   Allows the user to know the sum of the leaevs in a given BST object
Notes:     Public version. Calls private version.
**********************************************************************************/
int BST::sumLeaves()
{
   return sumLeaves(root);
}

/***********************************************************************************
Function:  void insert(Node*& n, int x)
Arguments: A node pointer n (our initial node), and an integer (the value to insert)
Returns:   N/A
Purpose:   Allows user to insert a node into a BST object
Notes:     Private version. Recursively implemented.
************************************************************************************/
void BST::insert(Node*& n, int x)
{
   if(n!=nullptr)
    {
     if(x < n->val)
        insert(n->left, x);
     else if(x > n->val)
        insert(n->right, x);
     }
     else
       {
        n = new Node;
        n->val = x;
        n->left = n->right = nullptr;
       }
}

/************************************************************************************
Function:  bool search(Node*& n, int x)
Arguments: A node pointer n (points to the initial node), an integer value of the node being searched for
Returns:   Boolean value. True if found. False otherwise.
Purpose:   Allows user to search for nodes in a BST object by value.
Notes:     Private version. Recursive implementation.
************************************************************************************/
bool BST::search(Node*& n, int x)
{
     if(n != nullptr)
      {
       if(x == n->val)
         return true;
       else if(x < n->val)
         return search(n->left, x);
       else
         return search(n->right, x);
      }
     return false;
}

/************************************************************************************
Function:  bool remove(Node*& n, int x)
Arguments: A node pointer n, pointing to the current node. An int x, the value of the node we are removing
Returns:   N/A
Purpose:   Allows user to remove nodes from a BST object by value
Notes:     Private version. Recursively Implemented
************************************************************************************/
bool BST::remove(Node*& n, int x)
{
     Node* tempNodePtr = nullptr;
     if(n != nullptr)
       {
        if(x < n->val)
         return  remove(n->left, x);
        else if(x > n->val)
         return  remove(n->right, x);
        else
           {
            if(n->left != nullptr && n->right != nullptr)
             {
              tempNodePtr = n->left;
              while(tempNodePtr->right != nullptr)
                 {
                  tempNodePtr = tempNodePtr->right;
                 }
	      n->val = tempNodePtr->val;
	      return remove(n->left, n->val);
             }
            else if(n->left == nullptr && n->right == nullptr)
	         {
  		  delete n;
		  n = nullptr;
                  return true;
		 }
	    else
		{
		 tempNodePtr = n;
		 if(tempNodePtr->left == nullptr)
                   {
			n = n->right;
                        delete tempNodePtr;
                        return true;
                   }
		 else if(tempNodePtr->right == nullptr)
                   {
			n = n->left;
		       delete tempNodePtr;
                       return true;
	  	   }
	        }
           }
       }
     return true;
}

/****************************************************************************
Function:  int sumLeaves(Node*& n)
Arguments: A node pointer n, the starting node
Returns:   An integer, the sum of the leaves in a BST object
Purpose:   Allows the user to calculate the number of leaf nodes in a BST object
Notes:	   Private version. Recursive implementation.
*****************************************************************************/
int BST::sumLeaves(Node*& n)
{
  if(n != nullptr)
    {
     if(n->left == nullptr && n->right == nullptr)
       {
        return n->val;
       }
     return sumLeaves(n->left) + sumLeaves(n->right);
    }
  return 0;
}
