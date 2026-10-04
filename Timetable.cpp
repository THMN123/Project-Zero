#include "Timetable.h"

using namespace std;

// ============================================================
//  Timetable class
// ============================================================
Timetable::Timetable() {
    courseID   = "";
    courseName = "";
    program    = "";
    dayOfWeek  = "";
    startTime  = "";
    endTime    = "";
    room       = "";
    lecturerID = "";
}

Timetable::Timetable(string cid, string cname, string prog, string day,
                     string start, string end, string r, string lecID) {
    courseID   = cid;
    courseName = cname;
    program    = prog;
    dayOfWeek  = day;
    startTime  = start;
    endTime    = end;
    room       = r;
    lecturerID = lecID;
}

string Timetable::getCourseID()   const { return courseID; }
string Timetable::getCourseName() const { return courseName; }
string Timetable::getProgram()    const { return program; }
string Timetable::getDayOfWeek()  const { return dayOfWeek; }
string Timetable::getStartTime()  const { return startTime; }
string Timetable::getEndTime()    const { return endTime; }
string Timetable::getRoom()       const { return room; }
string Timetable::getLecturerID() const { return lecturerID; }

void Timetable::setRoom(string r)      { room = r; }
void Timetable::setStartTime(string s) { startTime = s; }
void Timetable::setEndTime(string e)   { endTime = e; }

void Timetable::display() const {
    cout << "[" << program << "] "
         << courseID << " - " << courseName
         << " | " << dayOfWeek
         << " " << startTime << "-" << endTime
         << " | Room: " << room
         << " | Lect: " << lecturerID
         << endl;
}

// ============================================================
//  TimetableNode class
// ============================================================
TimetableNode::TimetableNode(Timetable t) {
    data  = t;
    left  = nullptr;
    right = nullptr;
}

// ============================================================
//  TimetableBST class
// ============================================================
TimetableBST::TimetableBST() {
    root = nullptr;
}

TimetableBST::~TimetableBST() {
    destroyTree(root);
}

void TimetableBST::destroyTree(TimetableNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void TimetableBST::insert(Timetable t) {
    root = insertRec(root, t);
}

TimetableNode* TimetableBST::insertRec(TimetableNode* node, Timetable t) {
    if (node == nullptr) {
        return new TimetableNode(t);
    }
    // Sort by program first, then courseID for clean grouping
    string key     = t.getProgram() + t.getCourseID() + t.getDayOfWeek();
    string nodeKey = node->data.getProgram() + node->data.getCourseID() + node->data.getDayOfWeek();

    if (key < nodeKey) {
        node->left = insertRec(node->left, t);
    } else {
        node->right = insertRec(node->right, t);
    }
    return node;
}

// Display ALL entries in sorted order
void TimetableBST::displayAll() const {
    if (root == nullptr) {
        cout << "No timetable entries found." << endl;
        return;
    }
    inorderRec(root);
}

void TimetableBST::inorderRec(TimetableNode* node) const {
    if (node != nullptr) {
        inorderRec(node->left);
        node->data.display();
        inorderRec(node->right);
    }
}

// Show classes for a specific day across all programs
void TimetableBST::displayByDay(string day) const {
    cout << "--- Schedule for " << day << " ---" << endl;
    filterByDayRec(root, day);
}

void TimetableBST::filterByDayRec(TimetableNode* node, string day) const {
    if (node == nullptr) return;
    filterByDayRec(node->left, day);
    if (node->data.getDayOfWeek() == day) {
        node->data.display();
    }
    filterByDayRec(node->right, day);
}

// Show classes taught by a specific lecturer (across all their programs)
void TimetableBST::displayByLecturer(string lecID) const {
    cout << "--- Schedule for Lecturer: " << lecID << " ---" << endl;
    filterByLecturerRec(root, lecID);
}

void TimetableBST::filterByLecturerRec(TimetableNode* node, string lecID) const {
    if (node == nullptr) return;
    filterByLecturerRec(node->left, lecID);
    if (node->data.getLecturerID() == lecID) {
        node->data.display();
    }
    filterByLecturerRec(node->right, lecID);
}

// Show the full timetable for a specific program (used by students)
void TimetableBST::displayByProgram(string prog) const {
    cout << "--- Full Timetable: " << prog << " ---" << endl;
    filterByProgramRec(root, prog);
}

void TimetableBST::filterByProgramRec(TimetableNode* node, string prog) const {
    if (node == nullptr) return;
    filterByProgramRec(node->left, prog);
    if (node->data.getProgram() == prog) {
        node->data.display();
    }
    filterByProgramRec(node->right, prog);
}

void TimetableBST::displayByProgramAndDay(string prog, string day) const {
    cout << "--- " << prog << " | " << day << " ---" << endl;
    filterByProgramAndDayRec(root, prog, day);
}

void TimetableBST::filterByProgramAndDayRec(TimetableNode* node, string prog, string day) const {
    if (node == nullptr) return;
    filterByProgramAndDayRec(node->left, prog, day);
    if (node->data.getProgram() == prog && node->data.getDayOfWeek() == day) {
        node->data.display();
    }
    filterByProgramAndDayRec(node->right, prog, day);
}

void TimetableBST::clear() {
    destroyTree(root);
    root = nullptr;
}

void TimetableBST::displayByStudentModules(string prog, const string modules[], int modCount) const {
    displayByStudentModulesAndWeeklySchedule(prog, modules, modCount);
}

void TimetableBST::displayByStudentModulesAndWeeklySchedule(string prog, const string modules[], int modCount) const {
    string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    cout << "\n========================================================" << endl;
    cout << "     FULL 5-DAY WEEKLY SCHEDULE (MONDAY - FRIDAY)        " << endl;
    cout << "     PROGRAM: " << prog << endl;
    cout << "========================================================" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "\n>>> DAY: " << days[i] << " <<<" << endl;
        displayByStudentModulesAndDay(prog, modules, modCount, days[i]);
    }
    cout << "========================================================\n" << endl;
}

void TimetableBST::displayByStudentModulesAndDay(string prog, const string modules[], int modCount, string day) const {
    filterByStudentModulesAndDayRec(root, prog, modules, modCount, day);
}

void TimetableBST::filterByStudentModulesAndDayRec(TimetableNode* node, string prog, const string modules[], int modCount, string day) const {
    if (node == nullptr) return;
    filterByStudentModulesAndDayRec(node->left, prog, modules, modCount, day);
    
    if (node->data.getProgram() == prog && node->data.getDayOfWeek() == day) {
        bool match = false;
        for (int i = 0; i < modCount; i++) {
            if (node->data.getCourseID() == modules[i]) {
                match = true;
                break;
            }
        }
        if (match) {
            node->data.display();
        }
    }
    filterByStudentModulesAndDayRec(node->right, prog, modules, modCount, day);
}

void TimetableBST::filterByStudentModulesRec(TimetableNode* node, string prog, const string modules[], int modCount) const {
    if (node == nullptr) return;
    filterByStudentModulesRec(node->left, prog, modules, modCount);
    
    // Check if entry matches student's program and one of their registered modules
    if (node->data.getProgram() == prog) {
        bool match = false;
        for (int i = 0; i < modCount; i++) {
            if (node->data.getCourseID() == modules[i]) {
                match = true;
                break;
            }
        }
        if (match) {
            node->data.display();
        }
    }
    filterByStudentModulesRec(node->right, prog, modules, modCount);
}

bool TimetableBST::isConflict(string day, string start, string room, string lecID, string prog) const {
    return checkConflictRec(root, day, start, room, lecID, prog);
}

bool TimetableBST::checkConflictRec(TimetableNode* node, string day, string start, string room, string lecID, string prog) const {
    if (node == nullptr) return false;
    if (node->data.getDayOfWeek() == day && node->data.getStartTime() == start) {
        // Room conflict or lecturer conflict or cohort/program conflict at the exact same timeslot
        if (node->data.getRoom() == room || node->data.getLecturerID() == lecID || node->data.getProgram() == prog) {
            return true;
        }
    }
    return checkConflictRec(node->left, day, start, room, lecID, prog) ||
           checkConflictRec(node->right, day, start, room, lecID, prog);
}

// ============================================================
//  NATIONAL UNIVERSITY OF LESOTHO (NUL) COURSES & MASTER ENGINE
// ============================================================

static const ProgramInfo NUL_CATALOGUE[] = {
    // b01: BSc Information Systems
    {
        "b01", "BSc Information Systems", 4,
        {
            {"IS1501", "Introduction to Information Systems", 1, 1, "SCILT-101", "LEC_IS01"},
            {"CS1401", "Programming Fundamentals Principles", 1, 1, "CMP-LAB1", "LEC_CS01"},
            {"M111",   "Introductory Mathematics I",         1, 1, "SCILT-102", "LEC_MATH1"},
            {"ST111",  "Introduction to Statistics I",       1, 1, "SCILT-103", "LEC_STAT1"},
            
            {"IS1502", "Database Systems & Design",           1, 2, "SCILT-101", "LEC_IS02"},
            {"CS1402", "Object Oriented Programming I",      1, 2, "CMP-LAB1", "LEC_CS02"},
            {"M112",   "Calculus & Linear Algebra",          1, 2, "SCILT-102", "LEC_MATH2"},
            
            {"IS2501", "Systems Analysis & Design",           2, 1, "SCILT-201", "LEC_IS01"},
            {"CS2401", "Data Structures & Algorithms",        2, 1, "CMP-LAB2", "LEC_CS01"},
            {"IS2503", "Enterprise Architecture",             2, 1, "SCILT-202", "LEC_IS03"},
            
            {"IS2502", "Web Systems & Development",           2, 2, "CMP-LAB2", "LEC_IS02"},
            {"CS2402", "Database Management Systems",         2, 2, "CMP-LAB1", "LEC_CS02"},
            
            {"IS3501", "IT Project Management",               3, 1, "SCILT-301", "LEC_IS03"},
            {"CS3401", "Operating Systems",                   3, 1, "CMP-LAB3", "LEC_CS03"},
            
            {"IS4501", "IS Strategy & Governance",            4, 1, "SCILT-401", "LEC_IS01"},
            {"IS4599", "IS Senior Capstone Project",          4, 2, "SCILT-401", "LEC_IS01"}
        }, 16
    },
    // b02: BSc Computer Science
    {
        "b02", "BSc Computer Science", 4,
        {
            {"CS1401", "Programming Fundamentals Principles", 1, 1, "CMP-LAB1", "LEC_CS01"},
            {"M111",   "Introductory Mathematics I",         1, 1, "SCILT-102", "LEC_MATH1"},
            {"P111",   "General Physics I",                  1, 1, "SCIENCE-L1", "LEC_PHYS1"},
            
            {"CS1402", "Object Oriented Programming I",      1, 2, "CMP-LAB1", "LEC_CS02"},
            {"CS1404", "Discrete Structures",                1, 2, "CMP-102",  "LEC_CS03"},
            
            {"CS2401", "Data Structures & Algorithms",        2, 1, "CMP-LAB2", "LEC_CS01"},
            {"CS2403", "Computer Architecture & Assembly",    2, 1, "CMP-103",  "LEC_CS03"},
            
            {"CS2402", "Database Management Systems",         2, 2, "CMP-LAB1", "LEC_CS02"},
            {"CS2404", "Software Engineering Principles",     2, 2, "CMP-102",  "LEC_CS01"},
            
            {"CS3401", "Operating Systems",                   3, 1, "CMP-LAB3", "LEC_CS03"},
            {"CS3403", "Computer Networks & Protocols",       3, 1, "CMP-LAB2", "LEC_CS02"},
            
            {"CS4401", "Compiler Construction & Design",      4, 1, "CMP-104",  "LEC_CS03"},
            {"CS4499", "Computer Science Research Project",   4, 2, "CMP-LAB3", "LEC_CS01"}
        }, 13
    },
    // b03: BSc Biotechnology
    {
        "b03", "BSc Biotechnology", 4,
        {
            {"B111",   "Introductory Biology I",             1, 1, "SCIENCE-L2", "LEC_BIO1"},
            {"C111",   "General Chemistry I",                1, 1, "SCIENCE-L1", "LEC_CHEM1"},
            {"B112",   "Cell Biology & Genetics",            1, 2, "SCIENCE-L2", "LEC_BIO1"},
            {"B211",   "Microbiology Fundamentals",          2, 1, "SCIENCE-L3", "LEC_BIO2"},
            {"C211",   "Organic Chemistry I",                2, 1, "SCIENCE-L1", "LEC_CHEM2"},
            {"B311",   "Molecular Biology & Recombinant DNA",3, 1, "SCIENCE-L3", "LEC_BIO2"},
            {"B411",   "Industrial Biotechnology",           4, 1, "SCIENCE-L3", "LEC_BIO1"}
        }, 7
    },
    // b04: BBA Business Administration
    {
        "b04", "BBA Business Administration", 4,
        {
            {"BUS111", "Principles of Management",           1, 1, "SOC-101", "LEC_BUS1"},
            {"ACC111", "Financial Accounting I",             1, 1, "SOC-102", "LEC_ACC1"},
            {"ECO111", "Microeconomics I",                   1, 1, "SOC-103", "LEC_ECO1"},
            {"BUS112", "Organizational Behaviour",           1, 2, "SOC-101", "LEC_BUS1"},
            {"ACC112", "Financial Accounting II",            1, 2, "SOC-102", "LEC_ACC1"},
            {"BUS211", "Marketing Management",               2, 1, "SOC-201", "LEC_BUS2"},
            {"BUS311", "Corporate Finance",                  3, 1, "SOC-301", "LEC_ACC1"},
            {"BUS411", "Strategic Management",               4, 1, "SOC-401", "LEC_BUS1"}
        }, 8
    },
    // b05: BEng Electronics Engineering
    {
        "b05", "BEng Electronics Engineering", 5,
        {
            {"EG101",  "Engineering Drawing & CAD",          1, 1, "ENG-LAB1", "LEC_ENG1"},
            {"M111",   "Introductory Mathematics I",         1, 1, "SCILT-102", "LEC_MATH1"},
            {"P111",   "General Physics I",                  1, 1, "SCIENCE-L1", "LEC_PHYS1"},
            {"EG201",  "Circuit Theory I",                   2, 1, "ENG-LAB2", "LEC_ENG1"},
            {"EG202",  "Analogue Electronics",               2, 2, "ENG-LAB2", "LEC_ENG2"},
            {"EG301",  "Digital Signal Processing",          3, 1, "ENG-LAB3", "LEC_ENG2"},
            {"EG401",  "Microcontroller Systems",            4, 1, "ENG-LAB3", "LEC_ENG1"},
            {"EG501",  "Telecommunication Systems",          5, 1, "ENG-HALL", "LEC_ENG2"}
        }, 8
    }
};

static const int NUL_CATALOGUE_COUNT = 5;

void displayNULCatalogue() {
    cout << "\n========================================================" << endl;
    cout << "    NATIONAL UNIVERSITY OF LESOTHO (NUL) CATALOGUE     " << endl;
    cout << "========================================================" << endl;
    for (int i = 0; i < NUL_CATALOGUE_COUNT; i++) {
        cout << "[" << NUL_CATALOGUE[i].code << "] "
             << NUL_CATALOGUE[i].name
             << " (" << NUL_CATALOGUE[i].durationYears << " Years, "
             << NUL_CATALOGUE[i].moduleCount << " Modules)" << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

string getProgramNameByCode(string code) {
    for (int i = 0; i < NUL_CATALOGUE_COUNT; i++) {
        if (NUL_CATALOGUE[i].code == code || NUL_CATALOGUE[i].name == code) {
            return NUL_CATALOGUE[i].name;
        }
    }
    return code; // return as-is if already full name or unmatched
}

int getModulesForStudent(string progCode, int year, int semester, ModuleInfo outModules[]) {
    int count = 0;
    for (int i = 0; i < NUL_CATALOGUE_COUNT; i++) {
        if (NUL_CATALOGUE[i].code == progCode || NUL_CATALOGUE[i].name == progCode) {
            for (int m = 0; m < NUL_CATALOGUE[i].moduleCount; m++) {
                if (NUL_CATALOGUE[i].modules[m].year == year &&
                    NUL_CATALOGUE[i].modules[m].semester == semester) {
                    outModules[count++] = NUL_CATALOGUE[i].modules[m];
                }
            }
            break;
        }
    }
    return count;
}

void generateMasterTimetable(TimetableBST& bst) {
    bst.clear();
    
    string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    string timeslots[] = {"08:00", "10:00", "12:00", "14:00", "16:00"};
    
    int totalInserted = 0;
    
    for (int p = 0; p < NUL_CATALOGUE_COUNT; p++) {
        const ProgramInfo& prog = NUL_CATALOGUE[p];
        
        for (int m = 0; m < prog.moduleCount; m++) {
            const ModuleInfo& mod = prog.modules[m];
            
            bool scheduled = false;
            // Attempt to find a conflict-free day and timeslot
            for (int d = 0; d < 5 && !scheduled; d++) {
                for (int t = 0; t < 5 && !scheduled; t++) {
                    string day = days[d];
                    string startTime = timeslots[t];
                    string endTime = (startTime == "08:00") ? "10:00" :
                                     (startTime == "10:00") ? "12:00" :
                                     (startTime == "12:00") ? "14:00" :
                                     (startTime == "14:00") ? "16:00" : "18:00";
                    
                    // Cohort string (Program + Year) to prevent student cohort overlap
                    string cohort = prog.name + " Yr" + to_string(mod.year);
                    
                    if (!bst.isConflict(day, startTime, mod.defaultRoom, mod.defaultLecturer, cohort)) {
                        Timetable entry(mod.code, mod.name, prog.name, day, startTime, endTime, mod.defaultRoom, mod.defaultLecturer);
                        bst.insert(entry);
                        scheduled = true;
                        totalInserted++;
                    }
                }
            }
        }
    }
    cout << "\n[+] Master Timetable Engine successfully generated " 
         << totalInserted << " conflict-free timetable entries across all NUL Faculties!" << endl;
}

