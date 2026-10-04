// =============================================================
// CS3400 CAMPUS RESOURCE AND ACTIVITY MANAGEMENT SYSTEM
// Group Type A: Campus Facilities
// =============================================================

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Resource.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "PriorityQueue.h"
#include "Tree.h"
#include "Sorting.h"
#include "HashTable.h"
#include "Graph.h"
#include "User.h"
#include "UserHashTable.h"
#include "Timetable.h"

using namespace std;

// =============================================================
//  FORWARD DECLARATIONS
// =============================================================
void showAdminMenu();
void showStudentMenu();
void showLecturerMenu();

void loadData(LinkedList& resources, HashTable& resTable, Graph& graph,
              UserHashTable& users, TimetableBST& timetable);
void saveData(const LinkedList& resources, const UserHashTable& users,
              const TimetableBST& timetable);
void saveTimetableHelper(TimetableNode* node, ofstream& file);

// =============================================================
//  MENU DISPLAY FUNCTIONS
// =============================================================
void showAdminMenu() {
    cout << "\n========================================" << endl;
    cout << "     ADMIN MENU                         " << endl;
    cout << "========================================" << endl;
    cout << "--- Resources ---" << endl;
    cout << "1.  Add a Resource" << endl;
    cout << "2.  Display All Resources" << endl;
    cout << "3.  Search Resource (Linked List)" << endl;
    cout << "4.  Hash Table Lookup (O(1))" << endl;
    cout << "5.  Update Resource Status" << endl;
    cout << "6.  Remove Resource" << endl;
    cout << "7.  Undo Last Deletion" << endl;
    cout << "--- Requests ---" << endl;
    cout << "8.  View/Process Pending Requests (Queue)" << endl;
    cout << "9.  View/Process Priority Requests (Heap)" << endl;
    cout << "--- Organisation ---" << endl;
    cout << "10. Sort Resources" << endl;
    cout << "11. Tree Operations (BST)" << endl;
    cout << "--- Timetable ---" << endl;
    cout << "12. Add Timetable Entry (Manual)" << endl;
    cout << "13. View Full Master Timetable" << endl;
    cout << "14. View NUL Course Catalogue" << endl;
    cout << "15. Auto-Generate Master Timetable (Engine)" << endl;
    cout << "--- Navigation ---" << endl;
    cout << "16. Campus Navigation (Graph)" << endl;
    cout << "17. Shortest Path (Dijkstra)" << endl;
    cout << "--- Users ---" << endl;
    cout << "18. Register New User" << endl;
    cout << "19. Display All Users" << endl;
    cout << "0.  Save & Logout" << endl;
    cout << "Enter your choice: ";
}

void showStudentMenu() {
    cout << "\n========================================" << endl;
    cout << "     STUDENT MENU                       " << endl;
    cout << "========================================" << endl;
    cout << "1. View Available Resources" << endl;
    cout << "2. Submit Resource Request" << endl;
    cout << "3. Submit Priority Request" << endl;
    cout << "4. Register/View My Registered Modules & Personal Timetable" << endl;
    cout << "5. View My Program Timetable (by Day)" << endl;
    cout << "6. View Full Program Timetable" << endl;
    cout << "7. Campus Navigation (Graph)" << endl;
    cout << "8. Shortest Path (Dijkstra)" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

void showLecturerMenu() {
    cout << "\n========================================" << endl;
    cout << "     LECTURER MENU                      " << endl;
    cout << "========================================" << endl;
    cout << "1. View Available Resources" << endl;
    cout << "2. Submit Resource Request" << endl;
    cout << "3. View My Teaching Schedule" << endl;
    cout << "4. View Full Timetable" << endl;
    cout << "5. Campus Navigation (Graph)" << endl;
    cout << "6. Shortest Path (Dijkstra)" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

// =============================================================
//  FILE I/O FUNCTIONS
// =============================================================
void loadData(LinkedList& resources, HashTable& resTable, Graph& graph,
              UserHashTable& users, TimetableBST& timetable) {
    // --- Load resources from resources.txt ---
    ifstream resFile("resources.txt");
    if (resFile.is_open()) {
        string line;
        while (getline(resFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string id, name, type, loc, capStr, status;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, loc, ',');
            getline(ss, capStr, ',');
            getline(ss, status, ',');
            if (!id.empty()) {
                int capacity = stoi(capStr);
                Resource r(id, name, type, loc, capacity, status);
                resources.insertAtEnd(r);
                resTable.insert(id, r);
            }
        }
        resFile.close();
        cout << "[+] Loaded resources.txt" << endl;
    }

    // --- Load users from users.txt ---
    ifstream usrFile("users.txt");
    if (usrFile.is_open()) {
        string line;
        while (getline(usrFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string id, pass, role, name, prog;
            getline(ss, id,   ',');
            getline(ss, pass, ',');
            getline(ss, role, ',');
            getline(ss, name, ',');
            getline(ss, prog, ',');   // program field (may be empty for ADMIN)
            if (!id.empty()) {
                users.insert(id, User(id, pass, role, name, prog));
            }
        }
        usrFile.close();
        cout << "[+] Loaded users.txt" << endl;
    }

    // --- Load campus locations from locations.txt ---
    ifstream locFile("locations.txt");
    if (locFile.is_open()) {
        string loc;
        while (getline(locFile, loc)) {
            if (!loc.empty()) graph.addLocation(loc);
        }
        locFile.close();
        cout << "[+] Loaded locations.txt" << endl;
    }

    // --- Load timetable from timetables.txt ---
    ifstream ttFile("timetables.txt");
    if (ttFile.is_open()) {
        string line;
        while (getline(ttFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string cid, cname, prog, day, start, end, room, lecID;
            getline(ss, cid,   ',');
            getline(ss, cname, ',');
            getline(ss, prog,  ',');
            getline(ss, day,   ',');
            getline(ss, start, ',');
            getline(ss, end,   ',');
            getline(ss, room,  ',');
            getline(ss, lecID, ',');
            if (!cid.empty()) {
                timetable.insert(Timetable(cid, cname, prog, day, start, end, room, lecID));
            }
        }
        ttFile.close();
        cout << "[+] Loaded timetables.txt" << endl;
    }

    // If master timetable is currently empty (e.g. fresh start), generate NUL Master Timetable automatically
    if (ttFile.fail() || true) { // checked in caller or after loading if empty
        // We will ensure auto-generation if tree is empty after load below
    }
}

void saveData(const LinkedList& resources, const UserHashTable& users,
              const TimetableBST& timetable) {
    // --- Save resources ---
    ofstream resFile("resources.txt");
    if (resFile.is_open()) {
        int size = resources.getSize();
        if (size > 0) {
            Resource* arr = new Resource[size];
            resources.toArray(arr);
            for (int i = 0; i < size; i++) {
                resFile << arr[i].getResourceID() << ","
                        << arr[i].getName() << ","
                        << arr[i].getType() << ","
                        << arr[i].getLocation() << ","
                        << arr[i].getCapacity() << ","
                        << arr[i].getStatus() << "\n";
            }
            delete[] arr;
        }
        resFile.close();
        cout << "[+] Saved resources.txt" << endl;
    }
}

// =============================================================
//  SHARED ACTION HELPERS
// =============================================================
void submitRequest(Queue& requests, const string& userInfo) {
    string reqId, res, time;
    cout << "Enter Request ID: ";
    getline(cin, reqId);
    cout << "Enter Requested Resource: ";
    getline(cin, res);
    cout << "Enter Request Time (e.g. 10:00): ";
    getline(cin, time);
    requests.enqueue(Request(reqId, userInfo, res, time, "Pending", 1));
    cout << "Request submitted!" << endl;
}

void submitPriorityRequest(PriorityQueue& pq, const string& userInfo) {
    string reqId, res, time;
    int prio;
    cout << "Enter Request ID: ";
    getline(cin, reqId);
    cout << "Enter Requested Resource: ";
    getline(cin, res);
    cout << "Enter Request Time: ";
    getline(cin, time);
    cout << "Priority (4=Emergency, 3=High, 2=Normal, 1=Low): ";
    cin >> prio;
    cin.ignore();
    pq.enqueue(Request(reqId, userInfo, res, time, "Pending", prio));
    cout << "Priority request submitted!" << endl;
}

void showNavMenu(Graph& campusMap) {
    int gChoice;
    cout << "\n--- Campus Navigation ---" << endl;
    cout << "1. Add Location" << endl;
    cout << "2. Add Pathway" << endl;
    cout << "3. Display Connections" << endl;
    cout << "4. BFS Traversal" << endl;
    cout << "5. DFS Traversal" << endl;
    cout << "Enter choice: ";
    cin >> gChoice;
    cin.ignore();

    if (gChoice == 1) {
        string loc;
        cout << "Enter location name: ";
        getline(cin, loc);
        campusMap.addLocation(loc);
    } else if (gChoice == 2) {
        string l1, l2;
        int w;
        cout << "From: "; getline(cin, l1);
        cout << "To:   "; getline(cin, l2);
        cout << "Distance (weight): "; cin >> w; cin.ignore();
        campusMap.addConnection(l1, l2, w);
    } else if (gChoice == 3) {
        campusMap.displayConnections();
    } else if (gChoice == 4) {
        string start;
        cout << "Starting location: ";
        getline(cin, start);
        campusMap.BFS(start);
    } else if (gChoice == 5) {
        string start;
        cout << "Starting location: ";
        getline(cin, start);
        campusMap.DFS(start);
    }
}

// =============================================================
//  MAIN
// =============================================================
int main() {
    // Core data structures
    LinkedList resources;
    Queue requests;
    Stack undoStack;
    PriorityQueue priorityRequests(100);
    BST resourceTree;
    HashTable resourceTable(100);
    Graph campusMap(50);
    UserHashTable users;
    TimetableBST timetable;

    cout << "========================================" << endl;
    cout << "  CAMPUS RESOURCE MANAGEMENT SYSTEM     " << endl;
    cout << "========================================" << endl;

    // Load all data from disk
    loadData(resources, resourceTable, campusMap, users, timetable);

    // Auto-generate NUL Master Timetable if empty on startup
    generateMasterTimetable(timetable);

    // Seed a default admin if no users were loaded
    if (users.search("admin") == nullptr) {
        users.insert("admin", User("admin", "admin123", "ADMIN", "System Administrator"));
        cout << "[!] Default admin created: ID=admin  Pass=admin123" << endl;
    }

    // Seed some sample campus locations if none were loaded
    if (campusMap.getNumVertices() == 0) {
        campusMap.addLocation("Library");
        campusMap.addLocation("ICTLAB");
        campusMap.addLocation("Main Hall");
        campusMap.addLocation("Admin Block");
        campusMap.addLocation("Science Block");
        campusMap.addConnection("Library", "ICTLAB", 3);
        campusMap.addConnection("Library", "Main Hall", 5);
        campusMap.addConnection("Main Hall", "Admin Block", 2);
        campusMap.addConnection("Admin Block", "Science Block", 4);
        campusMap.addConnection("ICTLAB", "Science Block", 6);
    }

    // Seed some sample resources if none were loaded
    if (resources.getSize() == 0) {
        Resource r1("LAB101", "ICTLAB", "Laboratory", "Science Block", 40, "Available");
        Resource r2("LEC201", "Main Hall", "Lecture Room", "Main Hall", 150, "Occupied");
        Resource r3("PRJ001", "Projector A", "Equipment", "Store Room", 1, "Available");
        resources.insertAtEnd(r1);
        resources.insertAtEnd(r2);
        resources.insertAtEnd(r3);
        resourceTable.insert("LAB101", r1);
        resourceTable.insert("LEC201", r2);
        resourceTable.insert("PRJ001", r3);
    }

    // =============================================================
    //  WELCOME SCREEN + AUTH LOOP
    // =============================================================
    bool running = true;
    while (running) {

        // ---- Welcome / Auth menu ----
        cout << "\n========================================" << endl;
        cout << "  CAMPUS RESOURCE MANAGEMENT SYSTEM     " << endl;
        cout << "========================================" << endl;
        cout << "  1. Login" << endl;
        cout << "  2. Sign Up" << endl;
        cout << "  0. Exit" << endl;
        cout << "========================================" << endl;
        cout << "  Choose an option: ";

        int authChoice;
        cin >> authChoice;
        cin.ignore();

        // ---- EXIT ----
        if (authChoice == 0) {
            running = false;
            break;
        }

        // ---- SIGN UP ----
        if (authChoice == 2) {
            cout << "\n--- SIGN UP ---" << endl;
            string uid, pass, pass2, role2, name, prog;

            cout << "Full Name    : "; getline(cin, name);
            cout << "User ID      : "; getline(cin, uid);

            if (users.search(uid) != nullptr) {
                cout << "[!] That User ID is already taken. Please try another." << endl;
                continue;
            }

            cout << "Password     : "; getline(cin, pass);
            cout << "Confirm Pass : "; getline(cin, pass2);

            if (pass != pass2) {
                cout << "[!] Passwords do not match. Please try again." << endl;
                continue;
            }

            cout << "Role (STUDENT / LECTURER) : "; getline(cin, role2);

            if (role2 != "STUDENT" && role2 != "LECTURER") {
                cout << "[!] Invalid role. Only STUDENT or LECTURER accounts can be created here." << endl;
                continue;
            }

            if (role2 == "STUDENT") {
                displayNULCatalogue();
                cout << "Program Code (e.g. b01 for BSc Information Systems): ";
                getline(cin, prog);
                prog = getProgramNameByCode(prog);
            } else {
                cout << "Program(s) you teach (comma-separated, e.g. BSc CS,BSc IT): ";
                getline(cin, prog);
            }

            users.insert(uid, User(uid, pass, role2, name, prog));
            cout << "[+] Account created! You can now log in." << endl;
            continue;
        }

        // ---- LOGIN ----
        if (authChoice == 1) {
            cout << "\n--- LOGIN ---" << endl;
            cout << "User ID  : ";
            string loginID;
            getline(cin, loginID);
            cout << "Password : ";
            string loginPass;
            getline(cin, loginPass);

            User* loggedIn = users.search(loginID);
            if (loggedIn == nullptr || loggedIn->getPassword() != loginPass) {
                cout << "[!] Invalid credentials. Try again." << endl;
                continue;
            }

            cout << "\nWelcome, " << loggedIn->getFullName()
                 << "! [" << loggedIn->getRole() << "]" << endl;

            string role = loggedIn->getRole();
            bool loggedInSession = true;

            // =============================================================
            //  ADMIN SESSION
            // =============================================================
            while (loggedInSession && role == "ADMIN") {
                showAdminMenu();
                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    string id, name, type, location, status;
                    int capacity;
                    cout << "Resource ID: "; getline(cin, id);
                    cout << "Name: ";        getline(cin, name);
                    cout << "Type: ";        getline(cin, type);
                    cout << "Location: ";    getline(cin, location);
                    cout << "Capacity: ";    cin >> capacity; cin.ignore();
                    cout << "Status: ";      getline(cin, status);
                    Resource newRes(id, name, type, location, capacity, status);
                    resources.insertAtEnd(newRes);
                    resourceTable.insert(id, newRes);
                    cout << "[+] Resource added." << endl;

                } else if (choice == 2) {
                    cout << "\n--- All Resources ---" << endl;
                    resources.displayAll();

                } else if (choice == 3) {
                    string id;
                    cout << "Resource ID to search: "; getline(cin, id);
                    Resource* found = resources.searchResource(id);
                    if (found) found->display();
                    else cout << "Not found." << endl;

                } else if (choice == 4) {
                    string id;
                    cout << "Resource ID: "; getline(cin, id);
                    Resource* found = resourceTable.search(id);
                    if (found) found->display();
                    else cout << "Not found in Hash Table." << endl;

                } else if (choice == 5) {
                    string id, newStatus;
                    cout << "Resource ID: "; getline(cin, id);
                    Resource* found = resources.searchResource(id);
                    if (found) {
                        cout << "Current Status: " << found->getStatus() << endl;
                        cout << "New Status: "; getline(cin, newStatus);
                        found->setStatus(newStatus);
                        cout << "[+] Updated." << endl;
                    } else cout << "Not found." << endl;

                } else if (choice == 6) {
                    string id;
                    cout << "Resource ID to remove: "; getline(cin, id);
                    Resource* toRemove = resources.searchResource(id);
                    if (toRemove != nullptr) {
                        undoStack.push(*toRemove);
                        resources.deleteResource(id);
                    } else {
                        cout << "Not found." << endl;
                    }

                } else if (choice == 7) {
                    if (undoStack.isEmpty()) {
                        cout << "Nothing to undo." << endl;
                    } else {
                        Resource restored = undoStack.pop();
                        resources.insertAtEnd(restored);
                        resourceTable.insert(restored.getResourceID(), restored);
                        cout << "[+] Restored: " << restored.getResourceID() << endl;
                    }

                } else if (choice == 8) {
                    int qc;
                    cout << "1. Process next  2. View queue: ";
                    cin >> qc; cin.ignore();
                    if (qc == 1) requests.dequeue();
                    else requests.displayPending();

                } else if (choice == 9) {
                    int pc;
                    cout << "1. Process next  2. View queue: ";
                    cin >> pc; cin.ignore();
                    if (pc == 1) priorityRequests.dequeue();
                    else priorityRequests.displayPending();

                } else if (choice == 10) {
                    int size = resources.getSize();
                    if (size == 0) { cout << "No resources." << endl; }
                    else {
                        Resource* arr = new Resource[size];
                        resources.toArray(arr);
                        int sc;
                        cout << "1. Quick Sort (by ID)  2. Bubble Sort (by Capacity): ";
                        cin >> sc; cin.ignore();
                        if (sc == 1) { Sorter::quickSort(arr, 0, size - 1); cout << "Sorted by ID:" << endl; }
                        else         { Sorter::bubbleSort(arr, size);        cout << "Sorted by Capacity:" << endl; }
                        for (int i = 0; i < size; i++) arr[i].display();
                        delete[] arr;
                    }

                } else if (choice == 11) {
                    int tc;
                    cout << "1. Add to Tree  2. Inorder  3. Preorder  4. Search: ";
                    cin >> tc; cin.ignore();
                    if (tc == 1) {
                        string id, name, type, loc, stat; int cap;
                        cout << "ID: ";       getline(cin, id);
                        cout << "Name: ";     getline(cin, name);
                        cout << "Type: ";     getline(cin, type);
                        cout << "Location: "; getline(cin, loc);
                        cout << "Capacity: "; cin >> cap; cin.ignore();
                        cout << "Status: ";   getline(cin, stat);
                        resourceTree.insert(Resource(id, name, type, loc, cap, stat));
                    } else if (tc == 2) resourceTree.displayInorder();
                    else if (tc == 3)   resourceTree.displayPreorder();
                    else if (tc == 4) {
                        string id; cout << "ID: "; getline(cin, id);
                        Resource* f = resourceTree.search(id);
                        if (f) f->display(); else cout << "Not found." << endl;
                    }

                } else if (choice == 12) {
                    string cid, cname, prog, day, start, end, room, lecID;
                    cout << "Course ID: ";               getline(cin, cid);
                    cout << "Course Name: ";             getline(cin, cname);
                    cout << "Program (e.g. BSc CS): ";   getline(cin, prog);
                    cout << "Day (e.g. Monday): ";       getline(cin, day);
                    cout << "Start Time (e.g. 08:00): "; getline(cin, start);
                    cout << "End Time (e.g. 10:00): ";   getline(cin, end);
                    cout << "Room ID: ";                 getline(cin, room);
                    cout << "Lecturer ID: ";             getline(cin, lecID);
                    timetable.insert(Timetable(cid, cname, prog, day, start, end, room, lecID));
                    cout << "[+] Timetable entry added." << endl;

                } else if (choice == 13) {
                    cout << "\n--- Master Timetable ---" << endl;
                    timetable.displayAll();

                } else if (choice == 14) {
                    displayNULCatalogue();

                } else if (choice == 15) {
                    generateMasterTimetable(timetable);

                } else if (choice == 16) {
                    showNavMenu(campusMap);

                } else if (choice == 17) {
                    string start;
                    cout << "Find shortest path from: "; getline(cin, start);
                    campusMap.dijkstra(start);

                } else if (choice == 18) {
                    string uid, pass, role2, name, progCode;
                    cout << "User ID: ";                         getline(cin, uid);
                    cout << "Password: ";                        getline(cin, pass);
                    cout << "Role (ADMIN/LECTURER/STUDENT): ";   getline(cin, role2);
                    cout << "Full Name: ";                       getline(cin, name);
                    if (role2 == "STUDENT") {
                        displayNULCatalogue();
                        cout << "Program Code (e.g. b01 for BSc Information Systems): "; getline(cin, progCode);
                        string fullProgName = getProgramNameByCode(progCode);
                        users.insert(uid, User(uid, pass, role2, name, fullProgName));
                    } else if (role2 == "LECTURER") {
                        cout << "Program(s) taught (comma-sep): "; getline(cin, progCode);
                        users.insert(uid, User(uid, pass, role2, name, progCode));
                    } else {
                        users.insert(uid, User(uid, pass, role2, name, ""));
                    }
                    cout << "[+] User registered successfully." << endl;

                } else if (choice == 19) {
                    users.displayAll();

                } else if (choice == 0) {
                    cout << "Saving data..." << endl;
                    saveData(resources, users, timetable);
                    loggedInSession = false;
                } else {
                    cout << "Invalid choice." << endl;
                }
            } // end ADMIN while

            // =============================================================
            //  STUDENT SESSION
            // =============================================================
            while (loggedInSession && role == "STUDENT") {
                showStudentMenu();
                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    cout << "\n--- Available Resources ---" << endl;
                    resources.displayAll();
                } else if (choice == 2) {
                    submitRequest(requests, loggedIn->getUserID());
                } else if (choice == 3) {
                    submitPriorityRequest(priorityRequests, loggedIn->getUserID());
                } else if (choice == 4) {
                    int year, semester;
                    cout << "\n--- Student Module Registration & Timetable ---" << endl;
                    cout << "Student Program: " << loggedIn->getProgram() << endl;
                    cout << "Enter your current Academic Year (1-4): "; cin >> year;
                    cout << "Enter current Semester (1-2): ";          cin >> semester; cin.ignore();
                    
                    ModuleInfo mods[20];
                    int mCount = getModulesForStudent(loggedIn->getProgram(), year, semester, mods);
                    
                    if (mCount == 0) {
                        cout << "No prescribed modules found for Year " << year << " Semester " << semester << "." << endl;
                    } else {
                        cout << "\n[+] Automatically assigned prescribed modules for Year " << year << " Semester " << semester << ":" << endl;
                        string modCodes[20];
                        for (int i = 0; i < mCount; i++) {
                            modCodes[i] = mods[i].code;
                            cout << "  - " << mods[i].code << ": " << mods[i].name << " (Room: " << mods[i].defaultRoom << ")" << endl;
                        }
                        
                        timetable.displayByStudentModules(loggedIn->getProgram(), modCodes, mCount);
                    }
                } else if (choice == 5) {
                    // Pull a specific day's classes for THIS student's program
                    string day;
                    cout << "Enter day (e.g. Monday): "; getline(cin, day);
                    timetable.displayByProgramAndDay(loggedIn->getProgram(), day);
                } else if (choice == 6) {
                    // Full weekly timetable for THIS student's program
                    timetable.displayByProgram(loggedIn->getProgram());
                } else if (choice == 7) {
                    showNavMenu(campusMap);
                } else if (choice == 8) {
                    string start;
                    cout << "Starting location: "; getline(cin, start);
                    campusMap.dijkstra(start);
                } else if (choice == 0) {
                    loggedInSession = false;
                } else {
                    cout << "Invalid choice." << endl;
                }
            } // end STUDENT while

            // =============================================================
            //  LECTURER SESSION
            // =============================================================
            while (loggedInSession && role == "LECTURER") {
                showLecturerMenu();
                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    cout << "\n--- Available Resources ---" << endl;
                    resources.displayAll();
                } else if (choice == 2) {
                    submitRequest(requests, loggedIn->getUserID());
                } else if (choice == 3) {
                    // Show only classes this lecturer teaches
                    timetable.displayByLecturer(loggedIn->getUserID());
                } else if (choice == 4) {
                    timetable.displayAll();
                } else if (choice == 5) {
                    showNavMenu(campusMap);
                } else if (choice == 6) {
                    string start;
                    cout << "Starting location: "; getline(cin, start);
                    campusMap.dijkstra(start);
                } else if (choice == 0) {
                    loggedInSession = false;
                } else {
                    cout << "Invalid choice." << endl;
                }
            } // end LECTURER while

        } // end if (authChoice == 1)

    } // end while (running)

    cout << "\nSystem shut down. Goodbye!" << endl;
    return 0;
}
