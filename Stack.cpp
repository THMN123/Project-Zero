#include "Stack.h"

using namespace std;

StackNode::StackNode(Resource res) {
    data = res;
    next = nullptr;
}

Stack::Stack() {
    topNode = nullptr;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(Resource res) {
    StackNode* newNode = new StackNode(res);
    newNode->next = topNode;
    topNode = newNode;
}

Resource Stack::pop() {
    if (isEmpty()) {
        // Return an empty resource if stack is empty
        return Resource();
    }
    
    StackNode* temp = topNode;
    Resource poppedData = temp->data;
    topNode = topNode->next;
    delete temp;
    
    return poppedData;
}

Resource* Stack::peek() const {
    if (isEmpty()) return nullptr;
    return &(topNode->data);
}

bool Stack::isEmpty() const {
    return topNode == nullptr;
}
