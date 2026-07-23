#ifndef MOVEMENTHISTORY_H
#define MOVEMENTHISTORY_H

class MovementHistory {

private:
    struct Move {
        int x,y;
        Move* next;
        Move(int x,int y);
    };
    Move* head;

public:
    MovementHistory();
    ~MovementHistory();

    void addMove(int x,int y);
    void showHistory();
};

#endif