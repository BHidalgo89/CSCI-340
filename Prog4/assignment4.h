/*****************************************************************************
PROGRAMMER : Branden Hidalgo
ZID        : Z1663752
SECTION    : 1
ASSIGNMENT : 4
DUE DATE   : 02/27/19
*****************************************************************************/
#ifndef ASSIGNMNET4_H
#define ASSIGNMENT4_H
#include <stack>
#include <iomanip>
#include <iostream>

using namespace std;

class Queue {
    private:
        std::stack<int> s1, s2;
    public:
        bool empty() const;
        int size() const;
        int front();
        int back();
        void push(const int& val);
        void pop();
};

#endif
