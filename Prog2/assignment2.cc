/*****************************************************************************
PROGRAMMER: Branden Hidalgo
ZID:        Z1663752
SECTION:    1
ASSIGNMENT: 2
DUE DATE:   02/06/19
*****************************************************************************/

#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cstdlib>
#include<vector>

using namespace std;

const int NO_ITEMS = 10;
const int ITEM_W = 6;
const int LOW = 1;
const int HIGH = 100;
const int DATA_SIZE = 100;
const int SEARCH_SIZE = 50;
const int DATA_SEED = 11;
const int SEARCH_SEED = 7;

/*************************************************************************************************
FUNCTION:  void genRndNums(vector<int>& v, int seed)
ARGUMENTS: One reference to a vector of integers, one integer variable.
RETURNS:   N/A
PURPOSE:   Generates random integers in range [1-100] and stores them in vector v.
NOTES:
*************************************************************************************************/
void genRndNums( vector<int>& v, int seed ){
 srand(seed);                   //Initializes random number generator
 for(auto it = v.begin(); it<v.end(); it++)
  {
   int rVal = (rand() % (HIGH - LOW + 1) + LOW);         //Generate random integer and store in rVal
   *it = rVal;                                          //Store random integer in element
  }
}

/**************************************************************************************************
FUNCTION:  bool linearSearch(const vector<int>& inputVec, int x)
ARGUMENTS: One constant reference to a vector of integers, one integer variable.
RETURNS:   A boolean value. If search is successful, returns true. Otherwise, returns false.
PURPOSE:   A linear search algorithm. Searches for x in inputVec.
NOTES:
**************************************************************************************************/
bool linearSearch( const vector<int>& inputVec, int x){
 auto it = find(inputVec.begin(), inputVec.end(), x);
 if(it != inputVec.end())
   return true;
 else
   return false;
}

/*************************************************************************************************
FUNCTION:  bool binary_search(const vector<int>& inputVec, int x)
ARGUMENTS: One constant reference to a vector of integers, one integer variable.
RETURNS:   A boolean value. If search is successful, returns true. Otherwise, returns false.
PURPOSE:   A binary search algorithm. Searches for x in inputVec.
NOTES:
**************************************************************************************************/
bool binarySearch( const vector<int>& inputVec, int x)
{
 if(binary_search(inputVec.begin(), inputVec.end(), x))
   return true;
 else
   return false;
}

/**************************************************************************************************
FUNCTION:  int search(const vector<int>& inputVec, const vector<int>& searchVec, bool(*p)(const vect$
ARGUMENTS: Two references to constant vectors of integers, one pointer to a search routine p().
RETURNS:   Integer value representing the total number of successful searches.
PURPOSE:   A generic search algorithm. Takes a pointer to the search routine p() and calls p() for
           each element of vector searchVec in vector inputVec. It computes the total number of
           successful searches and returns that value to the main() routine as an input argument to
           printStat(), which is used to print out the final statistics for a search algorithm.
NOTES:
**************************************************************************************************/
int search( const vector<int>& inputVec, const vector<int>& searchVec,
            bool (*p)( const vector<int>&, int) ){
 int cnt = 0;
 for(auto it = searchVec.begin(); it != searchVec.end(); it++)
  {
   if(p(inputVec, *it))
    {
     cnt++;
    }
  }
 return cnt;
}

/*************************************************************************************************
FUNCTION:  void sortVector(vector<int>& inputVec)
ARGUMENTS: One reference to a vector of integers.
RETURNS:   N/A
PURPOSE:   A sort algorithm. Sorts the elements of inputVec in ascending order.
NOTES:
*************************************************************************************************/
void sortVector (vector<int>& inputVec){
 sort(inputVec.begin(), inputVec.end());
}

/*************************************************************************************************
FUNCTION:  void printStat(int totalSucCnt, int vec_size)
ARGUMENTS: Two integer variables. totalSucCnt is the total number of successful comparisons.
           vec_size is the size of the test vector.
RETURNS:   N/A
PURPOSE:   Prints the percent of successful searces as floating-point numbers on stdout.
NOTES:
*************************************************************************************************/
void printStat (int totalSucCnt, int vec_size){
 float z = (static_cast<float>(totalSucCnt) / vec_size) * 100 ;
 cout << "Successful searches: " << z << ".00% " << endl;
}

/************************************************************************************************
FUNCTION:  void print_vec(const vector<int>& vec)
ARGUMENTS: One constant reference to a vector of integers.
RETURNS:   N/A
PURPOSE:   Displays the contents of vec on standard output. Prints exactly NO_ITEMS = 10 numbers
           on a single line, except perhaps the last line.
NOTES:
************************************************************************************************/
void print_vec( const vector<int>& vec ){
 int cnt = 0;
 for(auto it = vec.begin(); it < vec.end(); it++)
  {
   cout << setprecision(4) << setw(ITEM_W) << *it ;
   cnt++;
   if(cnt % NO_ITEMS == 0 && cnt != 0)
     {
     cout << endl;
     cnt = 0;
     }
  }
}

int main() {
    vector<int> inputVec(DATA_SIZE);
    vector<int> searchVec(SEARCH_SIZE);
    genRndNums(inputVec, DATA_SEED);
    genRndNums(searchVec, SEARCH_SEED);

    cout << "----- Data source: " << inputVec.size() << " randomly generated numbers ------" << endl;
    print_vec( inputVec );
    cout << "----- " << searchVec.size() << " random numbers to be searched -------" << endl;
    print_vec( searchVec );

    cout << "\nConducting linear search on unsorted data source ..." << endl;
    int linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on unsorted data source ..." << endl;
    int binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    sortVector( inputVec );

    cout << "\nConducting linear search on sorted data source ..." << endl;
    linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on sorted data source ..." << endl;
    binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    return 0;
}

