#ifndef BACKTRACKSTACK_H
#define BACKTRACKSTACK_H

#include <stack>
#include <utility>
using namespace std;

class BacktrackStack {
    private:
        stack<pair<int, int>> positions;

    public:
        void push(int x,int y);
        bool empty();
        bool backtrack(int& x,int& y);
};

#endif