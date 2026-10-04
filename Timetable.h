#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>
#include <iostream>

using namespace std;

// Timetable class: one entry per scheduled class
class Timetable {
private:
    string courseID;
    string courseName;
    string program;     // e.g., "BSc Computer Science" -- which program this class belongs to
    string dayOfWeek;   // e.g., "Monday"
    string startTime;   // e.g., "08:00"
    string endTime;     // e.g., "10:00"
    string room;        // e.g., "LAB101"
    string lecturerID;

public:
    // Constructors
    Timetable();
    Timetable(string cid, string cname, string prog, string day, string start,
              string end, string room, string lecID);

    // Getters
    string getCourseID()   const;
    string getCourseName() const;
    string getProgram()    const;
    string getDayOfWeek()  const;
    string getStartTime()  const;
    string getEndTime()    const;
    string getRoom()       const;
    string getLecturerID() const;

    // Setters
    void setRoom(string r);
    void setStartTime(string s);
    void setEndTime(string e);

    // Display
    void display() const;
};

// TimetableNode - the node class for the BST
class TimetableNode {
public:
    Timetable data;
    TimetableNode* left;
    TimetableNode* right;

    TimetableNode(Timetable t);
};

// TimetableBST - ordered by courseID so searches are O(log n)
class TimetableBST {
private:
    TimetableNode* root;

    TimetableNode* insertRec(TimetableNode* node, Timetable t);
    void inorderRec(TimetableNode* node) const;
    void filterByDayRec(TimetableNode* node, string day) const;
    void filterByLecturerRec(TimetableNode* node, string lecID) const;
    void destroyTree(TimetableNode* node);

public:
    TimetableBST();
    ~TimetableBST();

    void insert(Timetable t);
    void displayAll()                             const;
    void displayByDay(string day)                 const;
    void displayByLecturer(string lecID)          const;
    void displayByProgram(string prog)            const;
    void displayByProgramAndDay(string prog, string day) const;

private:
    void filterByProgramRec(TimetableNode* node, string prog)           const;
    void filterByProgramAndDayRec(TimetableNode* node, string prog, string day) const;
    void filterByStudentModulesRec(TimetableNode* node, string prog, const string modules[], int modCount) const;
    void filterByStudentModulesAndDayRec(TimetableNode* node, string prog, const string modules[], int modCount, string day) const;
    bool checkConflictRec(TimetableNode* node, string day, string start, string room, string lecID, string prog) const;

public:
    void clear();
    void displayByStudentModules(string prog, const string modules[], int modCount) const;
    void displayByStudentModulesAndWeeklySchedule(string prog, const string modules[], int modCount) const;
    void displayByStudentModulesAndDay(string prog, const string modules[], int modCount, string day) const;
    bool isConflict(string day, string start, string room, string lecID, string prog) const;
};

// Course / Program structure for NUL Catalogue
struct ModuleInfo {
    string code;
    string name;
    int year;
    int semester;
    string defaultRoom;
    string defaultLecturer;
};

struct ProgramInfo {
    string code;        // e.g. "b01"
    string name;        // e.g. "BSc Information Systems"
    int durationYears;  // e.g. 4
    ModuleInfo modules[30];
    int moduleCount;
};

// Catalogue & Master Engine Helper Functions
void displayNULCatalogue();
string getProgramNameByCode(string code);
int getModulesForStudent(string progCode, int year, int semester, ModuleInfo outModules[]);
void generateMasterTimetable(TimetableBST& bst);

#endif // TIMETABLE_H
