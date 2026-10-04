#ifndef STACK_H
#define STACK_H

#include "Resource.h"
#include <iostream>

using namespace std;

// StackNode class instead of struct
class StackNode {
public:
    Resource data;
    StackNode* next;

    StackNode(Resource res);
};

// Stack class for LIFO operations (Undo Deletion)
class Stack {
private:
    StackNode* topNode;

public:
    Stack();
    ~Stack();

    void push(Resource res);
    Resource pop();
    Resource* peek() const;
    bool isEmpty() const;
};

#endif // STACK_H
