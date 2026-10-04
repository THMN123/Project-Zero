#include "Resource.h"

using namespace std;

// Default constructor
Resource::Resource() {
    resourceID = "";
    name = "";
    type = "";
    location = "";
    capacity = 0;
    status = "Available";
}

// Parameterized constructor
Resource::Resource(string id, string n, string t, string loc, int cap, string stat) {
    resourceID = id;
    name = n;
    type = t;
    location = loc;
    capacity = cap;
    status = stat;
}

// Getters
string Resource::getResourceID() const { return resourceID; }
string Resource::getName() const { return name; }
string Resource::getType() const { return type; }
string Resource::getLocation() const { return location; }
int Resource::getCapacity() const { return capacity; }
string Resource::getStatus() const { return status; }

// Setters
void Resource::setResourceID(string id) { resourceID = id; }
void Resource::setName(string n) { name = n; }
void Resource::setType(string t) { type = t; }
void Resource::setLocation(string loc) { location = loc; }
void Resource::setCapacity(int cap) { capacity = cap; }
void Resource::setStatus(string stat) { status = stat; }

// Display method
void Resource::display() const {
    cout << "ID: " << resourceID 
         << " | Name: " << name 
         << " | Type: " << type 
         << " | Location: " << location 
         << " | Capacity: " << capacity 
         << " | Status: " << status << endl;
}
