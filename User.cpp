#include "User.h"

using namespace std;

User::User() {
    userID = "";
    password = "";
    role = "STUDENT";
    fullName = "";
    program = "";
}

User::User(string id, string pass, string userRole, string name, string prog) {
    userID = id;
    password = pass;
    role = userRole;
    fullName = name;
    program = prog;
}

string User::getUserID()   const { return userID; }
string User::getPassword() const { return password; }
string User::getRole()     const { return role; }
string User::getFullName() const { return fullName; }
string User::getProgram()  const { return program; }

void User::setPassword(string pass)  { password = pass; }
void User::setRole(string userRole)  { role = userRole; }
void User::setProgram(string prog)   { program = prog; }

void User::display() const {
    cout << "ID: "      << userID
         << " | Name: " << fullName
         << " | Role: " << role
         << " | Program: " << (program.empty() ? "N/A" : program)
         << endl;
}
