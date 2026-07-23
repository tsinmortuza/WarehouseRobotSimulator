#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <vector>
using namespace std;

struct Task {
    int id;
    int x,y;
    Task(int id,int x,int y);
};

class TaskQueue {
    private:
        vector<Task> tasks;
    public:
        void enqueue(int id,int x,int y);
        bool empty();
        std::vector<Task> getAllTasks();
        void clear();
        void display();
};

#endif