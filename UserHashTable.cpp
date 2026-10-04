#include "UserHashTable.h"

using namespace std;

UserHashNode::UserHashNode(string k, User v) {
    key = k;
    value = v;
    next = nullptr;
}

UserHashTable::UserHashTable(int size) {
    tableSize = size;
    table = new UserHashNode*[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

UserHashTable::~UserHashTable() {
    for (int i = 0; i < tableSize; i++) {
        UserHashNode* entry = table[i];
        while (entry != nullptr) {
            UserHashNode* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    delete[] table;
}

int UserHashTable::hashFunction(string key) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;
}

void UserHashTable::insert(string key, User value) {
    int hashValue = hashFunction(key);
    UserHashNode* prev = nullptr;
    UserHashNode* entry = table[hashValue];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        entry = new UserHashNode(key, value);
        if (prev == nullptr) {
            table[hashValue] = entry;
        } else {
            prev->next = entry;
        }
    } else {
        entry->value = value;
    }
}

User* UserHashTable::search(string key) const {
    int hashValue = hashFunction(key);
    UserHashNode* entry = table[hashValue];
    while (entry != nullptr) {
        if (entry->key == key) {
            return &(entry->value);
        }
        entry = entry->next;
    }
    return nullptr;
}

void UserHashTable::remove(string key) {
    int hashValue = hashFunction(key);
    UserHashNode* prev = nullptr;
    UserHashNode* entry = table[hashValue];
    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }
    if (entry == nullptr) return;
    if (prev == nullptr) {
        table[hashValue] = entry->next;
    } else {
        prev->next = entry->next;
    }
    delete entry;
}

void UserHashTable::displayAll() const {
    cout << "--- Registered Users ---" << endl;
    for (int i = 0; i < tableSize; i++) {
        UserHashNode* entry = table[i];
        while (entry != nullptr) {
            entry->value.display();
            entry = entry->next;
        }
    }
}
