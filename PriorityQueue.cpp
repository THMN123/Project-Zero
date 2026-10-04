#include "PriorityQueue.h"

using namespace std;

PriorityQueue::PriorityQueue(int cap) {
    capacity = cap;
    size = 0;
    heap = new Request[capacity];
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

void PriorityQueue::heapifyUp(int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap[index].getPriority() > heap[parent].getPriority()) {
        // Swap
        Request temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;

        index = parent;
        parent = (index - 1) / 2;
    }
}

void PriorityQueue::heapifyDown(int index) {
    int maxIndex = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < size && heap[leftChild].getPriority() > heap[maxIndex].getPriority()) {
        maxIndex = leftChild;
    }
    
    if (rightChild < size && heap[rightChild].getPriority() > heap[maxIndex].getPriority()) {
        maxIndex = rightChild;
    }

    if (index != maxIndex) {
        // Swap
        Request temp = heap[index];
        heap[index] = heap[maxIndex];
        heap[maxIndex] = temp;

        heapifyDown(maxIndex);
    }
}

void PriorityQueue::enqueue(Request req) {
    if (isFull()) {
        cout << "Priority Queue is full. Cannot enqueue." << endl;
        return;
    }
    
    heap[size] = req;
    heapifyUp(size);
    size++;
    cout << "Priority Request " << req.getRequestID() << " added." << endl;
}

void PriorityQueue::dequeue() {
    if (isEmpty()) {
        cout << "Priority Queue is empty." << endl;
        return;
    }
    
    cout << "Processed priority request: " << heap[0].getRequestID() << endl;
    
    heap[0] = heap[size - 1];
    size--;
    
    if (size > 0) {
        heapifyDown(0);
    }
}

Request* PriorityQueue::peekFront() const {
    if (isEmpty()) return nullptr;
    return &heap[0];
}

void PriorityQueue::displayPending() const {
    if (isEmpty()) {
        cout << "No pending priority requests." << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        heap[i].display();
    }
}

bool PriorityQueue::isEmpty() const {
    return size == 0;
}

bool PriorityQueue::isFull() const {
    return size == capacity;
}
