#include "Request.h"

using namespace std;

Request::Request() {
    requestID = "";
    userInfo = "";
    requestedResource = "";
    requestTime = "";
    requestStatus = "Pending";
    priority = 1;
}

Request::Request(string id, string user, string res, string time, string status, int prio) {
    requestID = id;
    userInfo = user;
    requestedResource = res;
    requestTime = time;
    requestStatus = status;
    priority = prio;
}

string Request::getRequestID() const { return requestID; }
string Request::getUserInfo() const { return userInfo; }
string Request::getRequestedResource() const { return requestedResource; }
string Request::getRequestTime() const { return requestTime; }
string Request::getRequestStatus() const { return requestStatus; }
int Request::getPriority() const { return priority; }

void Request::setRequestID(string id) { requestID = id; }
void Request::setUserInfo(string user) { userInfo = user; }
void Request::setRequestedResource(string res) { requestedResource = res; }
void Request::setRequestTime(string time) { requestTime = time; }
void Request::setRequestStatus(string status) { requestStatus = status; }
void Request::setPriority(int prio) { priority = prio; }

void Request::display() const {
    cout << "Req ID: " << requestID 
         << " | User: " << userInfo 
         << " | Resource: " << requestedResource 
         << " | Priority: " << priority
         << " | Time: " << requestTime 
         << " | Status: " << requestStatus << endl;
}
