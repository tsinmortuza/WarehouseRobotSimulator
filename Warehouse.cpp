#include "Warehouse.h"

#include <bits/stdc++.h>
using namespace std;

// CONSTRUCTOR
Warehouse::Warehouse() {

    int defaultGrid[ROWS][COLS] = {
        {0,0,0,0,0,0,0,0,0,0},{0,1,1,0,0,0,1,1,1,0},
        {0,0,0,0,1,0,0,0,0,0},{0,1,0,0,1,0,1,1,0,0},
        {0,1,0,0,0,0,0,0,0,0},{0,1,1,1,1,0,1,0,1,0},
        {0,0,0,0,0,0,1,0,1,0},{0,1,1,1,1,0,0,0,1,0},
        {0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0}};

    for (int i=0; i< ROWS; i++) {
        for (int j=0; j< COLS; j++) {
            grid[i][j] = defaultGrid[i][j];
        }
    }
}

// CHECK VALID CELL
bool Warehouse::isValid(int x,int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS &&
        grid[x][y] == 0;
}

// MANHATTAN DISTANCE
int Warehouse::manhattanDistance(int x1,int y1,int x2,int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// DISPLAY WAREHOUSE
void Warehouse::display(int robotX,int robotY) {
    cout << "\nWarehouse:\n";
    cout << "R = Robot\n";
    cout << "# = Obstacle\n";
    cout << ". = Free Space\n\n";

    for (int i=0; i< ROWS; i++) {
        for (int j=0; j< COLS; j++) {
            if (i == robotX && j == robotY) 
                cout << "R ";
            else if (grid[i][j] == 1) 
                cout << "# ";
            else
                cout << ". ";
            
        }
        cout << endl;
    }
}

// BFS SHORTEST PATH
vector<pair<int, int>>
Warehouse::findShortestPath(int startX,int startY,
    int targetX,int targetY) {

    vector<vector<bool>>visited(ROWS,vector<bool>(COLS,false));

    vector<vector<pair<int, int>>>
        parent(ROWS,vector<pair<int, int>>(COLS,{-1, -1}));

    queue<pair<int, int>> q;
    q.push({startX,startY});
    visited[startX][startY] = true;

    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;

        if (x == targetX && y == targetY) 
            break;

        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = {x,y};
                q.push({nx,ny});
            }
        }
    }

    // No path
    if (!visited[targetX][targetY]) 
        return {};
    
    // Reconstruct path
    vector< pair <int, int>> path;
    int x = targetX;
    int y = targetY;

    while (!(x == startX && y == startY)) {
        path.push_back({x,y});
        pair<int, int> previous = parent[x][y];
        x = previous.first;
        y = previous.second;
    }

    path.push_back({startX,startY});
    reverse(path.begin(),path.end());
    return path;
}

// DYNAMIC GREEDY
// FIND NEAREST TASK
int Warehouse::findNearestTask(const vector<Task>& tasks,
    int robotX,int robotY) {
    if (tasks.empty()) 
        return -1;

    int nearestIndex = 0;
    int nearestDistance = INT_MAX;
    
    for (int i=0; i< tasks.size(); i++) {
        int distance = manhattanDistance(robotX,robotY,
                        tasks[i].x,tasks[i].y);

        if (distance < nearestDistance) {
            nearestDistance = distance;
            nearestIndex = i;
        }
    }
    return nearestIndex;
}