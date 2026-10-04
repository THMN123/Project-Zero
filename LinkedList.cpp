#include "LinkedList.h"

using namespace std;

// Node constructor
Node::Node(Resource res) {
    data = res;
    next = nullptr;
}

// LinkedList constructor
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

// LinkedList destructor to free dynamic memory
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Insert at the beginning of the list
void LinkedList::insertAtBeginning(Resource res) {
    Node* newNode = new Node(res);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

// Insert at the end of the list
void LinkedList::insertAtEnd(Resource res) {
    Node* newNode = new Node(res);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Insert at a specific position (1-indexed)
void LinkedList::insertAtPosition(Resource res, int position) {
    if (position <= 1) {
        insertAtBeginning(res);
        return;
    }

    Node* newNode = new Node(res);
    Node* current = head;
    for (int i = 1; i < position - 1 && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr || current == tail) {
        // If position is beyond the end, just insert at the end
        delete newNode; // Delete the node we just created since insertAtEnd will make a new one
        insertAtEnd(res);
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Delete a resource by its ID
void LinkedList::deleteResource(string id) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    if (head->data.getResourceID() == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
        cout << "Resource " << id << " deleted successfully." << endl;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data.getResourceID() != id) {
        current = current->next;
    }

    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = temp->next;
        if (temp == tail) {
            tail = current;
        }
        delete temp;
        cout << "Resource " << id << " deleted successfully." << endl;
    } else {
        cout << "Resource " << id << " not found." << endl;
    }
}

// Traverse and display all resources
void LinkedList::displayAll() const {
    if (head == nullptr) {
        cout << "No resources available." << endl;
        return;
    }
    
    Node* current = head;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

int LinkedList::getSize() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void LinkedList::toArray(Resource arr[]) const {
    int i = 0;
    Node* current = head;
    while (current != nullptr) {
        arr[i] = current->data;
        i++;
        current = current->next;
    }
}

// Search for a resource by ID
Resource* LinkedList::searchResource(string id) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.getResourceID() == id) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}
