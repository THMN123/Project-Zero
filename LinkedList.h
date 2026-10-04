#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Resource.h"
#include <iostream>

using namespace std;

// Node class instead of struct, adhering to the user rule
class Node {
public:
    Resource data;
    Node* next;

    // Constructor
    Node(Resource res);
};

// LinkedList class to manage the list of resources
class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor and Destructor
    LinkedList();
    ~LinkedList();

    // Insertion
    void insertAtBeginning(Resource res);
    void insertAtEnd(Resource res);
    void insertAtPosition(Resource res, int position);

    // Deletion
    void deleteResource(string id);

    // Traversal and Display
    void displayAll() const;
    int getSize() const;
    void toArray(Resource arr[]) const;

    // Searching
    Resource* searchResource(string id) const;
};

#endif // LINKEDLIST_H
