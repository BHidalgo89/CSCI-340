/***********************************************************************
Programmer: Branden Hidalgo
Zid:	    Z1663752
Section:    1
Assignment: 3
Due Date:   02/14/19
***********************************************************************/

#include <iostream>
#include <iomanip>
#include <set>

const int NO_ITEMS = 6;
const int ITEM_W = 4;

using namespace std;

/*****************************************************************************
Function:  void sieve(set<int>& s, const int lower, const int upper)
Arguments: A reference to a set of integers, Two constant integers
Returns:   N/A
Purpose:   Applies the Sieve of Eratosthenes algorithm to remove all nonprime
           numbers from the integer set s.
Notes:     s = {lower, ..., upper}
****************************************************************************/
void sieve(set<int>& s, const int lower, const int upper)
{
 set<int>::iterator it1, it2;
 int m = 2;
 for(it1 = s.begin(); it1 != s.end(); it1++)
  {
   if(*it1 % m == 0 && *it1 % 1 ==0)
     {
      s.erase(*it1);
     }
     m++;
//   for(it2 = it1; it2 != s.end(); it2++)
//    {
//     if(((*it1)*(*it1) <= upper) && (*it1 % *it2 == 0))
//       {
//        s.erase(*it1);
//      }
//    }
  }
}

/***************************************************************************
Function:  void print_primes(const set<int>& s, const int lower, const int upper)
Arguments: A reference to a set of integers, Two constant integers
Returns:   N/A
Purpose:   Prints the elements in the integer set s.
Notes:     NO_ITEMS = 6 primes per line and ITEM_W = 4 spaces allocated for
           each prime.
*****************************************************************************/
void print_primes( const set<int>& s, const int lower, const int upper)
{
  int cnt = 0;
  set<int>::iterator it;
  for(it = s.begin(); it != s.end(); it++)
    {
     if(cnt < NO_ITEMS)
       {
        cout << setw(ITEM_W) << *it ;
        cnt++;
       }
     else
       {
        cout << endl;
        cout << setw(ITEM_W) << *it << endl ;
        cnt = 1;
       }
    }
}

/*****************************************************************************
Function:  void run_game(set<int>& s)
Arguments: Maintains a loop to take imputs from a user. Asks the user for the
           range of prime numbers.
Returns:   N/A
Purpose:   Maintains a loop to take inputs from a user. Asks the user for the
           range of prime numbers. Invokes sieve() and print_primes()
Notes:     Once the results are displayed, the user will be asked whether to
           continue or quit the game. In case of continuing the game, the user
           will be sked for values of the range again. The game continues until
           the user requests to stop.
*****************************************************************************/
void run_game(set<int>& s)
{
 int lower, upper;
 int cnt = 0;
 int cont = 1;
 while(cont == 1)
   {
    cout << "Please enter lower boundary: " << endl;
    cin >> lower;
    while(lower < 2)
      {
       cout << "Lower boundary must have a value of at least 2. Please enter lower boundary: " << endl;
       cin >> lower;
      }
    cout << "Please enter upper boundary: " << endl;
    cin >> upper;
    while(upper <= lower)
      {
       cout << "Upper boundary must be greater than " << lower << ". Please enter upper boundary: " << endl;
       cin >> upper;
      }
    for(int i = lower; i < upper; i++)
      {
       s.insert(cnt);
       cnt++;
      }
    sieve(s, lower, upper);
    print_primes(s, lower, upper);
    cout << endl << "Would you like to continue? Please enter 1 to continue or 0 to quit: " << endl;
    cin >> cont;
   }
}

int main() {
    set<int> s;
    run_game(s);
    return 0;
}
