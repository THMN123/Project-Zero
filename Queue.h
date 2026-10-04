#ifndef QUEUE_H
#define QUEUE_H

#include "Request.h"
#include <iostream>

using namespace std;

// QueueNode class instead of struct
class QueueNode {
public:
    Request data;
    QueueNode* next;

    QueueNode(Request req);
};

// Queue class for FIFO Request processing
class Queue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;

public:
    Queue();
    ~Queue();

    void enqueue(Request req);
    void dequeue();
    void displayPending() const;
    bool isEmpty() const;
    Request* peekFront() const;
};

#endif // QUEUE_H
