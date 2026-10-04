#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Resource.h"
#include <iostream>
#include <string>

using namespace std;

class HashNode {
public:
    string key;
    Resource value;
    HashNode* next;

    HashNode(string k, Resource v);
};

class HashTable {
private:
    int tableSize;
    HashNode** table;

    int hashFunction(string key) const;

public:
    HashTable(int size = 100);
    ~HashTable();

    void insert(string key, Resource value);
    Resource* search(string key) const;
    void remove(string key);
    void display() const;
};

#endif // HASHTABLE_H
