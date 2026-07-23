#include "TaskQueue.h"

#include <bits/stdc++.h>
using namespace std;

// TASK CONSTRUCTOR
Task::Task(int id,int x,int y) {
    this->id = id;
    this->x = x;
    this->y = y;
}

// ADD TASK
void TaskQueue::enqueue(int id,int x,int y) {
    tasks.push_back(Task(id,x,y));
}

// CHECK EMPTY
bool TaskQueue::empty() {
    return tasks.empty();
}

// GET ALL TASKS
vector<Task> TaskQueue::getAllTasks() {
    return tasks;
}

// CLEAR QUEUE
void TaskQueue::clear() {
    tasks.clear();
}

// DISPLAY TASKS
void TaskQueue::display() {
    if (tasks.empty()) {
        cout << "No pending tasks.\n";
        return;
    }

    cout << "\nPending Tasks:\n";
    for (const Task& task : tasks) {
        cout << "Item ID: " << task.id << " at ("
             << task.x << "," << task.y << ")\n";
    }
}