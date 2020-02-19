/******************************************************************************
PROGRAMMER : Branden Hidalgo
ZID        : Z1663752
SECTION    : 1
ASSIGNMENT : 4
DUE DATE   : 02/27/19
*****************************************************************************/
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include "assignment4.h"

using namespace std;
/****************************************************************************
FUNCTION:  bool empty() const
ARGUMENTS: N/A
RETURNS:   A boolean value
PURPOSE:   A constant function which is used for checking if a container is
	   empty or not.
NOTES:
****************************************************************************/
bool Queue::empty() const
{
 if(s1.size() > 0 || s2.size() > 0)
    return false;
 else
    return true;
}

/****************************************************************************
FUNCTION:  int size() const
ARGUMENTS: N/A
RETURNS:   An integer
PURPOSE:   A constant function which returns the number of elements in a
	   container.
NOTES:
****************************************************************************/
int Queue::size() const
{
 return s1.size() + s2.size();
// int cnt = 0;
// for(int i=0; i<s2.size(); i++)
// {
//    cnt++;
// }
// return cnt;
}
/****************************************************************************
FUNCTION:  int front()
ARGUMENTS: N/A
RETURNS:   An integer
PURPOSE:   A function used to return the oldest element in a container
NOTES:
***************************************************************************/
int Queue::front()
{
 if(s2.empty())
 {
   while(!s1.empty())
   {
     s2.push(s1.top());
     s1.pop();
   }
 }
 return s2.top();
}

/****************************************************************************
FUNCTION:  int back()
ARGUMENTS: N/A
RETURNS:   An integer
PURPOSE:   A function used to return the newest element in a container
NOTES:
***************************************************************************/
int Queue::back()
{
 if(s1.empty())
 {
   while(!s2.empty())
   {
     s1.push(s2.top());
     s2.pop();
   }
 }
 return s1.top();
}

/***************************************************************************
FUNCTION:  void push(const int& val)
ARGUMENTS: A constant reference to an integer
RETURNS:   N/A
PURPOSE:   Used to push a value into a container
NOTES:
***************************************************************************/
void Queue::push(const int& val)
{
   s1.push(val);
}

/****************************************************************************
FUNCTION:  void pop();
ARGUMENTS: N/A
RETURNS:   N/A
PURPOSE:   Used to remove the oldest element from a container
NOTES:
****************************************************************************/
void Queue::pop()
{
  s2.pop();
}

int main() {
    Queue q;
    string op;
    int val = 0;

   cout << "operation -- size front end" << endl;
   cin >> op;
   while ( !cin.eof() ) {
        if ( op == "push" ) {
            cin >> val;
            q.push( val );
            cout << op << " " << val << "    -- ";
        }
        else if ( op == "pop" ) {
            q.pop();
            cout << op << "       -- ";
        }
        else {
            cerr << "Error input: " << op << endl;
            return 1;
        }
        if ( q.size() > 0 )
            cout << setw(3) << q.size() << setw(5) << q.front() << setw(5) << q.back() << endl;
        else
            cout << setw(3) << q.size() << endl;

        cin >> op;
    }

    while ( !q.empty() )
        q.pop();

    return 0;
}
