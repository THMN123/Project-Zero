#ifndef USERHASHTABLE_H
#define USERHASHTABLE_H

#include "User.h"
#include <iostream>
#include <string>

using namespace std;

class UserHashNode {
public:
    string key;      // The userID
    User value;
    UserHashNode* next;

    UserHashNode(string k, User v);
};

class UserHashTable {
private:
    int tableSize;
    UserHashNode** table;

    int hashFunction(string key) const;

public:
    UserHashTable(int size = 50);
    ~UserHashTable();

    void insert(string key, User value);
    User* search(string key) const;
    void remove(string key);
    void displayAll() const;
};

#endif // USERHASHTABLE_H
