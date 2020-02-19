/******************************************************************************
Programmer:  Branden Hidalgo
Assignment:  7
Professor:   Minmei Hou
Couse:       CSCI 340
Section:     1
*******************************************************************************/

#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;
const int HEAP_SIZE = 50;

/****************************************************************************
Function:  void heapify(vector<int>& v, int heap_size, int r, bool (*compare)(int, int))
Arguments: A reference to a vector of integers, two integers, and a function pointer
Returns:   N/A
Purpose:   Heapifies a tree at the root position r, assuming r's two sub-trees are already heaps.
Notes:     Uses recursion
******************************************************************************/
void heapify(vector<int>& v, int heap_size, int r, bool (*compare)(int, int))
{
   int left = r*2;
   int right = r*2+1;

   if(left > heap_size)
      return;
   if(right > heap_size)
     {
      if(compare(v[left], v[r]))
        {
         int temp = v[left];
           v[left] = v[r];
             v[r] = temp;
        }
      else
	 return;
     }
   else
     {
      if(compare(v[left], v[right]))
        {
         if(compare(v[left], v[r]))
           {
            int temp = v[left];
              v[left] = v[r];
                v[r] = temp;
            heapify(v, heap_size, left, compare);
           }
         else
	    return;
        }
      else
	{
          if(compare(v[right], v[r]))
	    {
             int temp = v[right];
	      v[right] = v[r];
	     	  v[r] = temp;
             heapify(v, heap_size, right, compare);
            }
          else
	     return;
        }
     }
}

/*****************************************************************************
Function:  bool less_than(int e1, int e2)
Arguments: Two integers
Returns:   A boolean value
Purpose:   Compares two integers. Returns true if e1 is less than e2. Returns false otherwise.
Notes:     When this function is used as a predicate in build_heap, a min heap will be constructed
******************************************************************************/
bool less_than(int e1, int e2)
{
  if(e1 < e2)
     return true;
  else
     return false;
}

/******************************************************************************
Function:  bool greater_than(int e1, int e2)
Arguments: Two integers
Returns:   A boolean value
Purpose:   Compares two integers. Returns true if e1 is greater than e2. Returns false otherwise.
Notes:     When this function is used as a predicate in build_heap, a max heap is constructed.
******************************************************************************/
bool greater_than(int e1, int e2)
{
  if(e1 > e2)
     return true;
  else
     return false;
}

/*****************************************************************************
Function:  void build_heap(vector<int>& v, int heap_size, bool(*compare)(int, int))
Arguments: A reference to a vector of integers, an integer, a pointer to a boolean function
Returns:   N/A
Purpose:   Constructs a heap with heap_size elements in the vector
Notes:     compare is a funcction pointer (predicate) to compare two integers. Will invoke heapify.
******************************************************************************/
void build_heap(vector<int>& v, int heap_size, bool(*compare)(int, int))
{
      for(int r = heap_size/2; r != 0; r--)
         {
          heapify(v, heap_size, r, compare);
         }
      for(int r = 1; r <= heap_size/2; r++)
         {
          heapify(v, heap_size, r, compare);
         }
}

/*****************************************************************************
Function:  int extract_heap(vector<int>& v, int& heap_size, bool (*compare)(int, int))
Arguments: A reference to a vector of integers, a reference to an integer, a pointer to a boolean function
Returns:   An integer
Purpose:   Extracts the root of the heap recorded in v, fills the root with the last element of the current heap, updates heap_size, "heapifies" at the root, and returns the old root value
Notes:     Will invoke heapify()
*****************************************************************************/
int extract_heap(vector<int>& v, int& heap_size, bool (*compare)(int, int))
{
   int temp = v[1];
   v[1] = v[heap_size];
   v[heap_size] = temp;
   heap_size--;
   heapify(v, heap_size, 1, compare);
   return temp;
}

/*****************************************************************************
Function:  void heap_sort(vector<int>& v, int heap_size, bool (*compare)(int, int)
Arguments: A reference to a vector of integers, an integer, a pointer to a boolean function
Returns:   An integer
Purpose:   Implements the heap sort algorithm
Hotes:     The heap may be sorted in ascending or descending order, depending on the predicate passed into compare
******************************************************************************/
void heap_sort(vector<int>& v, int heap_size, bool (*compare)(int, int))
{
   if(v.empty())
     {
      cout << "Heap is empty.";
     }
   else
     {
      while(heap_size > 0)
         {
          extract_heap(v, heap_size, compare);
         }
      reverse(v.begin() +1, v.end());
     }
}

/****************************************************************************
Function:  void print_vector(vector<int>& v, int pos, int size)
Arguments: A reference to a vector of integers, two integers.
Returns:   N/A
Purpose:   Displays size number of elements contained in vector v starting at pos.
Notes:     Shows 8 elements per line. Each item occupies 5 spaces.
*****************************************************************************/
void print_vector(vector<int>& v, int pos, int size)
{
   while(pos <= size)
       {
        if(pos % 8 > 0)
         {
          cout << setw(5) << v[pos];
          pos++;
         }
        else
         {
          cout << setw(5) << v[pos];
          cout << endl;
          pos++;
         }
       }
        cout << endl;
}

int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake
    for (int i=1; i<=HEAP_SIZE; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+HEAP_SIZE+1 );

    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, HEAP_SIZE, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, HEAP_SIZE, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    return 0;
}
