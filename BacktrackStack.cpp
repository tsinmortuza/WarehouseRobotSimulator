#include "BacktrackStack.h"

#include <bits/stdc++.h>
using namespace std;

// PUSH POSITION
void BacktrackStack::push(int x,int y) {
    positions.push({x,y});
}

// CHECK EMPTY
bool BacktrackStack::empty() {
    return positions.empty();
}

// BACKTRACK
bool BacktrackStack::backtrack(int& x,int& y) {

    if (positions.empty()) 
        return false;

    pair<int, int> position = positions.top();
    positions.pop();
    x = position.first;
    y = position.second;

    return true;
}