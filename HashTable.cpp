#include "HashTable.h"

using namespace std;

HashNode::HashNode(string k, Resource v) {
    key = k;
    value = v;
    next = nullptr;
}

HashTable::HashTable(int size) {
    tableSize = size;
    table = new HashNode*[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; i++) {
        HashNode* entry = table[i];
        while (entry != nullptr) {
            HashNode* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }
    delete[] table;
}

int HashTable::hashFunction(string key) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % tableSize;
    }
    return hash;
}

void HashTable::insert(string key, Resource value) {
    int hashValue = hashFunction(key);
    HashNode* prev = nullptr;
    HashNode* entry = table[hashValue];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        entry = new HashNode(key, value);
        if (prev == nullptr) {
            table[hashValue] = entry;
        } else {
            prev->next = entry;
        }
    } else {
        // Update existing value
        entry->value = value;
    }
}

Resource* HashTable::search(string key) const {
    int hashValue = hashFunction(key);
    HashNode* entry = table[hashValue];

    while (entry != nullptr) {
        if (entry->key == key) {
            return &(entry->value);
        }
        entry = entry->next;
    }
    return nullptr;
}

void HashTable::remove(string key) {
    int hashValue = hashFunction(key);
    HashNode* prev = nullptr;
    HashNode* entry = table[hashValue];

    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr) {
        cout << "Key not found in hash table." << endl;
        return;
    }

    if (prev == nullptr) {
        table[hashValue] = entry->next;
    } else {
        prev->next = entry->next;
    }
    delete entry;
}

void HashTable::display() const {
    for (int i = 0; i < tableSize; i++) {
        if (table[i] != nullptr) {
            cout << "Bucket " << i << ": ";
            HashNode* entry = table[i];
            while (entry != nullptr) {
                cout << "[" << entry->key << "] -> ";
                entry = entry->next;
            }
            cout << "NULL" << endl;
        }
    }
}
