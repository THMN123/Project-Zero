#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

using namespace std;

// Resource class based on Group Type A: Campus Facilities
class Resource {
private:
    string resourceID;
    string name;
    string type;      // e.g., Lecture room, Laboratory, Building, Equipment
    string location;
    int capacity;
    string status;    // e.g., Available, Occupied, Under Maintenance

public:
    // Constructors
    Resource();
    Resource(string id, string n, string t, string loc, int cap, string stat);

    // Getters
    string getResourceID() const;
    string getName() const;
    string getType() const;
    string getLocation() const;
    int getCapacity() const;
    string getStatus() const;

    // Setters
    void setResourceID(string id);
    void setName(string n);
    void setType(string t);
    void setLocation(string loc);
    void setCapacity(int cap);
    void setStatus(string stat);

    // Display method
    void display() const;
};

#endif // RESOURCE_H
