#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Request.h"
#include <iostream>

using namespace std;

// Priority Queue class using a Max-Heap array
class PriorityQueue {
private:
    Request* heap;
    int capacity;
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue(int cap);
    ~PriorityQueue();

    void enqueue(Request req);
    void dequeue();
    Request* peekFront() const;
    void displayPending() const;
    bool isEmpty() const;
    bool isFull() const;
};

#endif // PRIORITYQUEUE_H
