/***************************************************************************
PROGRAMMER: Branden Hidalgo
ZID:	    Z1663752
SECTION:    1
ASSIGNMENT: 1
DUE DATE:   01/25/19
****************************************************************************/
#include <algorithm>
#include <vector>
#include <iostream>
#include<iomanip>
using namespace std;

const int DATA_SIZE = 200;
const int DATA_RANGE = 200;
const int DATA_SEED = 9;
const int SEARCH_SEED = 17;
const int NO_ITEMS = 8;
const int ITEM_W = 4;

/***************************************************************************
Function:  linear_search
Arguments: A constant reference to a vector of integers, a constant integer
           and a reference to an integer.
Returns:   If search is successful, returns an integer representing the
           position of the found element. Otherwise, returns integer -1.
Purpose:   Uses a linear search algorithm to search through a vector of
           integers for a desired value x. The number of comparisons is
           stored in the parameter comparisons.
Notes:
***************************************************************************/
int linear_search(const vector<int>& inputVec, const int x, int& comparisons)
{
 comparisons = 0;
 for(unsigned int i = 0; i < inputVec.size(); i++)
 {
  comparisons++;
  if(inputVec[i] == x)
    {
     return i;
    }
 }
  return -1;
}

/****************************************************************************
Function:  binary_search(const vector<int>& inputVec
Arguments: A constant reference to a vector of integers, a constant integer,
           and a reference to an integer
Returns:   If the search is successful, returns an integer representing the
           position of the found element. Otherwise, returns -1.
Purpose:   Uses a binary search algorithm to search for an integer x. The
           number of comparisons is saved in the parameter comparisons.
Notes:
****************************************************************************/

int binary_search(const vector<int>& inputVec, const int x, int& comparisons)
{
 int left = 0;
 int right = inputVec.size() -1;
 comparisons = 0;

 while(left <= right)
  {
   comparisons++;
   int mid = (left + right) / 2;
   if(x == inputVec[mid])
     return mid;
   else if(x < inputVec[mid])
     right = mid - 1;
   else
     left = mid + 1;
  }
  return -1;
}

/*****************************************************************************
Function:  print_vec(const vector<int>& vec)
Arguments: A constant reference to a vector of integers
Returns:   N/A
Purpose:   Displays the contents of a vector on standard output, printing
           exactly NO_ITEMS = 8 numbers on a single line, except the last line
Notes:
*****************************************************************************/
void print_vec( const vector<int>& vec )
{
 unsigned int i;
 for(i = 0; i < vec.size(); i++)
  {
     if(i % NO_ITEMS == 0 && i != 0)
    {
     cout << endl;
    }
   cout << setw(ITEM_W) << vec[i] ;
  }
}

void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, int (*search)(const vector<int>&, const int, int&) ) {
    int i, comparison = 0, sum = 0, found = 0;
    int res = 0;
    for (i = 0; i < (int)searchVec.size(); i++) {
        res = search( inputVec, searchVec[i], comparison );
        sum += comparison;
        if ( res >= 0 )
           found++;
    }
    cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size() << endl << endl;
}

int random_number() {
    return rand()%DATA_RANGE + 1;
}


int main () {

    // -------- create unique random numbers ------------------//
    vector<int> inputVec(DATA_SIZE);
    srand(DATA_SEED);
    generate(inputVec.begin(), inputVec.end(), random_number);
    sort(inputVec.begin(), inputVec.end());
    vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
    inputVec.resize( it - inputVec.begin() );
    random_shuffle( inputVec.begin(), inputVec.end() );

    cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl; 
    print_vec(inputVec);
    cout << endl;

    // -------- create random numbers to be searched ---------//
    vector<int> searchVec(DATA_SIZE/2);
    srand(SEARCH_SEED);
    generate(searchVec.begin(), searchVec.end(), random_number);

    cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
    print_vec(searchVec);
    cout << endl;

    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    sort(inputVec.begin(), inputVec.end());
    cout << "------- numbers in data source are now sorted ---------" << endl << endl;
    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    return 0;

}


