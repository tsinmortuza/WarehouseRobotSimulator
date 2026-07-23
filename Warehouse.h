#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "TaskQueue.h"

#include <vector>
#include <utility>
using namespace std;

class Warehouse {

    private:
        static const int ROWS = 10;
        static const int COLS = 10;

        int grid[ROWS][COLS];
        bool isValid(int x,int y);
        int manhattanDistance(int x1,int y1,int x2,int y2);

    public:
        Warehouse();
        void display(int robotX,int robotY);

        // BFS
        vector < pair < int, int >> 
            findShortestPath(int startX,int startY,
                int targetX,int targetY);

        // Dynamic Greedy
        int findNearestTask(const vector<Task>& tasks,
            int robotX,int robotY);
};

#endif