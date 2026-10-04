#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

using namespace std;

// Roles available in the system
// ADMIN: full access  |  STUDENT: limited access  |  LECTURER: can view timetables
class User {
private:
    string userID;
    string password;
    string role;     // "ADMIN", "STUDENT", or "LECTURER"
    string fullName;
    // For STUDENT  : their program of study  (e.g. "BSc Computer Science")
    // For LECTURER : the program(s) they teach, comma-separated (e.g. "BSc CS,BSc IT")
    string program;

public:
    // Constructors
    User();
    User(string id, string pass, string userRole, string name, string prog = "");

    // Getters
    string getUserID()   const;
    string getPassword() const;
    string getRole()     const;
    string getFullName() const;
    string getProgram()  const;

    // Setters
    void setPassword(string pass);
    void setRole(string userRole);
    void setProgram(string prog);

    // Display
    void display() const;
};

#endif // USER_H
