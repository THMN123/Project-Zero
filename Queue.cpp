#include "Queue.h"

using namespace std;

QueueNode::QueueNode(Request req) {
    data = req;
    next = nullptr;
}

Queue::Queue() {
    frontNode = nullptr;
    rearNode = nullptr;
}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(Request req) {
    QueueNode* newNode = new QueueNode(req);
    if (rearNode == nullptr) {
        frontNode = newNode;
        rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }
    cout << "Request " << req.getRequestID() << " added to the queue." << endl;
}

void Queue::dequeue() {
    if (isEmpty()) {
        cout << "Queue is already empty." << endl;
        return;
    }
    QueueNode* temp = frontNode;
    frontNode = frontNode->next;
    
    if (frontNode == nullptr) {
        rearNode = nullptr;
    }
    
    cout << "Processed request: " << temp->data.getRequestID() << endl;
    delete temp;
}

void Queue::displayPending() const {
    if (isEmpty()) {
        cout << "No pending requests." << endl;
        return;
    }
    QueueNode* current = frontNode;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

bool Queue::isEmpty() const {
    return frontNode == nullptr;
}

Request* Queue::peekFront() const {
    if (isEmpty()) return nullptr;
    return &(frontNode->data);
}
