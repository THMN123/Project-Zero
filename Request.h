#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>

using namespace std;

// Request class for managing resource requests
class Request {
private:
    string requestID;
    string userInfo;
    string requestedResource;
    string requestTime;
    string requestStatus;
    int priority; // Priority: 4 (Emergency) to 1 (Low)

public:
    // Constructors
    Request();
    Request(string id, string user, string res, string time, string status, int prio);

    // Getters
    string getRequestID() const;
    string getUserInfo() const;
    string getRequestedResource() const;
    string getRequestTime() const;
    string getRequestStatus() const;
    int getPriority() const;

    // Setters
    void setRequestID(string id);
    void setUserInfo(string user);
    void setRequestedResource(string res);
    void setRequestTime(string time);
    void setRequestStatus(string status);
    void setPriority(int prio);

    // Display
    void display() const;
};

#endif // REQUEST_H
