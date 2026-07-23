#include <bits/stdc++.h>

#include "AVLTree.h"
#include "TaskQueue.h"
#include "MovementHistory.h"
#include "BacktrackStack.h"
#include "Warehouse.h"

using namespace std;

// MAIN
int main() {
    // CREATE DATA STRUCTURES
    AVLTree inventory;
    TaskQueue taskQueue;
    MovementHistory movementHistory;
    BacktrackStack backtrackStack;
    Warehouse warehouse;

    // ROBOT STARTING POSITION
    int robotX = 1;
    int robotY = 1;
    int choice;

    cout << "\n------ WAREHOUSE ROBOT SIMULATION ------\n";
    // MAIN MENU LOOP
    while (true) {
        cout << "\n========== MENU ==========\n";
        cout << "1. Insert item into inventory\n";
        cout << "2. Display inventory (sorted)\n";
        cout << "3. Add task to queue\n";
        cout << "4. Process tasks (Dynamic Greedy + BFS)\n";
        cout << "5. Show movement history\n";
        cout << "6. Backtrack last move\n";
        cout << "7. Display warehouse\n";
        cout << "8. Show pending tasks\n";
        cout << "9. Exit\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        // CASE 1: INSERT INVENTORY
        if (choice == 1) {
            int number;
            cout << "Number of inputs: ";
            cin >> number;

            for (int i=0; i< number; i++) {
                int id;
                int x,y;
                cout << "Enter item id, x, y: ";
                cin >> id >> x >> y;

                inventory.insert(id,x,y);
            }
            cout << "Items inserted successfully.\n";
        }

        // CASE 2: DISPLAY INVENTORY
        else if (choice == 2) 
            inventory.display();

        // CASE 3: ADD TASK
        else if (choice == 3) {
            int id;
            int x,y;
            cout << "\nEnter task id, x, y: ";
            cin >> id >> x >> y;

            taskQueue.enqueue(id,x,y);
            cout << "Task added.\n";
        }

        // CASE 4: DYNAMIC GREEDY + BFS
        else if (choice == 4) {
            if (taskQueue.empty()) {
                cout << "\nNo pending tasks.\n";
                continue;
            }

            vector<Task> tasks = taskQueue.getAllTasks();
            taskQueue.clear();

            cout << "\nProcessing tasks...\n";
            // DYNAMIC GREEDY LOOP
            while (!tasks.empty()) {
                // FIND NEAREST TASK
                int nearestIndex = warehouse.
                        findNearestTask(tasks,robotX,robotY);
                Task currentTask = tasks[nearestIndex];

                cout << "\n----------------------------------\n";
                cout << "Dynamic Greedy selected Item "
                     << currentTask.id << "\n";

                cout << "Robot position: (" << robotX 
                     << "," << robotY << ")\n";
                cout << "Target position: (" << currentTask.x
                     << "," << currentTask.y << ")\n";

                // BFS
                vector<pair<int, int>> path =
                    warehouse.findShortestPath(robotX,robotY,
                        currentTask.x,currentTask.y);

                // NO PATH
                if (path.empty()) {
                    cout << "No path found to Item "
                         << currentTask.id << ". Task skipped.\n";
                    tasks.erase(tasks.begin() + nearestIndex);
                    continue;
                }

                cout << "BFS shortest path contains "
                     << path.size() - 1 << " moves.\n" << "Path: ";
                for (auto position : path) {
                    cout << "(" << position.first << ","
                         << position.second << ") ";
                }
                cout << "\n";

                // MOVE ROBOT
                for (int i=1; i< path.size(); i++) {
                    // Save previous position
                    // for backtracking
                    backtrackStack.push(robotX,robotY);
                    // Move robot
                    robotX = path[i].first;
                    robotY = path[i].second;

                    // Save movement history
                    movementHistory.addMove(robotX,robotY);
                }
                cout << "Picking item " << currentTask.id << " at (" 
                    << robotX << "," << robotY << ")\n";

                // REMOVE COMPLETED TASK
                tasks.erase(tasks.begin() + nearestIndex);

                // DYNAMIC GREEDY
                // Robot's new position is now used to
                // calculate the next nearest task.
                if (!tasks.empty()) {
                    cout << "Remaining tasks: " << tasks.size() << "\n";
                    cout << "Finding new nearest task...\n";
                }
            }
            cout << "\nAll tasks processed.\n";
            cout << "Robot is now at (" << robotX
                 << "," << robotY << ")\n";
        }

        // CASE 5: MOVEMENT HISTORY
        else if (choice == 5) {
            movementHistory.showHistory();
        }
        // CASE 6: BACKTRACK
        else if (choice == 6) {
            if (backtrackStack.backtrack(robotX,robotY)) {
                cout << "Robot backtracked to (" << robotX
                     << "," << robotY << ")\n";
            }
            else 
                cout << "No moves to backtrack.\n";
        }

        // CASE 7: DISPLAY WAREHOUSE
        else if (choice == 7) {
            warehouse.display(robotX,robotY);
        }
        // CASE 8: SHOW PENDING TASKS
        else if (choice == 8) {
            taskQueue.display();
        }
        // CASE 9: EXIT
        else if (choice == 9) {
            cout << "\nExiting program...\n";
            break;
        }
        // INVALID OPTION
        else 
            cout << "Invalid choice.\n";
    }

    return 0;
}