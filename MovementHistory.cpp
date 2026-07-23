#include "MovementHistory.h"

#include <bits/stdc++.h>
using namespace std;

// MOVE CONSTRUCTOR
MovementHistory::Move::Move(int x,int y) {
    this->x = x;
    this->y = y;
    next = nullptr;
}

// CONSTRUCTOR
MovementHistory::MovementHistory() {
    head = nullptr;
}

// ADD MOVEMENT
void MovementHistory::addMove(int x,int y) {
    Move* newMove = new Move(x,y);
    newMove->next = head;
    head = newMove;
}

// DISPLAY HISTORY
void MovementHistory::showHistory() {

    cout << "\nMovement history:\n";
    if (head == nullptr) {
        cout << "-----------No history found!-----------\n";
        return;
    }

    Move* current = head;
    while (current != nullptr) {
        cout << "(" << current->x << "," << current->y << ")\n";
        current = current->next;
    }
}

// DESTRUCTOR
MovementHistory::~MovementHistory() {

    while (head != nullptr) {
        Move* temp = head;
        head = head->next;
        delete temp;
    }
}