/*
 * Advising Assistance Program.cpp
 * 
 *
 * Purpose:
 *   This program helps academic advisors at ABCU view and manage course
 *   information for the Computer Science department. Advisors can:
 *     - Load course data from a CSV file
 *     - Print a sorted list of all courses
 *     - Display individual course information including prerequisites
 *
 * Data Structure:
 *   This version implements a Hash Table for efficient lookup by course number.
 *
 * Author: JakeTheSnake(JMG3000)
 * Date: 10/19/2025
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

// ===============================
// STRUCT DEFINITION
// ===============================

// Represents one course and its related information
struct Course {
    string courseNumber;             // e.g., "CSCI200"
    string courseTitle;              // e.g., "Data Structures"
    vector<string> prerequisites;    // e.g., {"CSCI101"}
};

// ===============================
// HELPER FUNCTIONS
// ===============================

// Removes leading and trailing whitespace from a string
string Trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";  // If string is empty or all spaces
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

// Converts a string to uppercase for consistent comparisons
string ToUpper(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Normalizes a course number by trimming and converting to uppercase
string NormalizeCourseNumber(const string& s) {
    return ToUpper(Trim(s));
}

// Splits a CSV line into tokens
vector<string> SplitCSV(const string& line) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        tokens.push_back(Trim(token));
    }
    return tokens;
}

// ===============================
// HASH TABLE CLASS
// ===============================

class HashTable {
private:
    // Each bucket contains a list of Courses (to handle collisions)
    vector<list<Course>> table;
    size_t tableSize;

    // Hash function — converts courseNumber into an index
    unsigned int Hash(string key) const {
        unsigned int hashValue = 0;
        for (char c : key) {
            hashValue = hashValue * 31 + toupper(c);
        }
        return hashValue % tableSize;
    }

public:
    // Constructor
    HashTable(size_t size = 20) {
        tableSize = size;
        table.resize(tableSize);
    }

    // Insert a new course into the hash table
    void Insert(const Course& course) {
        string key = NormalizeCourseNumber(course.courseNumber);
        unsigned int index = Hash(key);

        // Avoid duplicates
        for (const auto& c : table[index]) {
            if (NormalizeCourseNumber(c.courseNumber) == key) {
                cout << "Warning: Duplicate course '" << course.courseNumber << "' found. Skipping duplicate." << endl;
                return;
            }
        }

        table[index].push_back(course);
    }

    // Search for a course by course number
    Course* Search(const string& courseNumber) {
        string key = NormalizeCourseNumber(courseNumber);
        unsigned int index = Hash(key);

        for (auto& c : table[index]) {
            if (NormalizeCourseNumber(c.courseNumber) == key) {
                return &c;  // Return pointer to found course
            }
        }
        return nullptr;
    }

    // Retrieve all courses in a flat vector (for sorting and listing)
    vector<Course> GetAllCourses() const {
        vector<Course> allCourses;
        for (const auto& bucket : table) {
            for (const auto& course : bucket) {
                allCourses.push_back(course);
            }
        }
        return allCourses;
    }

    // Clear all stored data
    void Clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
    }
};

// ===============================
// CORE FUNCTIONALITY
// ===============================

// Loads courses from a CSV file into the hash table
bool LoadCourses(const string& filename, HashTable& courseTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file '" << filename << "'. Please check the file and try again.\n" << endl;
        return false;
    }

    courseTable.Clear();  // Clear any existing data
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        line = Trim(line);
        if (line.empty()) continue;

        vector<string> tokens = SplitCSV(line);

        if (tokens.size() < 2) {
            cout << "Warning (line " << lineNumber << "): Skipping invalid line." << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        courseTable.Insert(course);
    }

    file.close();

    cout << "Courses loaded successfully.\n" << endl;
    return true;
}

// Prints a sorted list of all courses (alphanumeric)
void PrintCourseList(const HashTable& courseTable) {
    vector<Course> allCourses = courseTable.GetAllCourses();

    if (allCourses.empty()) {
        cout << "No courses loaded. Please load data first.\n" << endl;
        return;
    }

    // Sort alphabetically by normalized course number
    sort(allCourses.begin(), allCourses.end(), [](const Course& a, const Course& b) {
        return NormalizeCourseNumber(a.courseNumber) < NormalizeCourseNumber(b.courseNumber);
        });

    cout << "\nHere is a sample schedule:" << endl;
    for (const auto& c : allCourses) {
        cout << c.courseNumber << ", " << c.courseTitle << endl;
    }
    cout << "\n";
}

// Prints detailed information for a specific course
void PrintCourseInfo(HashTable& courseTable, const string& query) {
    Course* course = courseTable.Search(query);

    if (course == nullptr) {
        cout << "Course not found.\n" << endl;
        return;
    }

    cout << "\n" << course->courseNumber << ", " << course->courseTitle << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None\n" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            cout << course->prerequisites[i];
            if (i < course->prerequisites.size() - 1) cout << ", ";
        }
        cout << "\n" << endl;
    }
}

// ===============================
// MENU SYSTEM
// ===============================

void DisplayMenu() {
    HashTable courseTable;  // Hash table data structure
    bool dataLoaded = false;

    cout << "Welcome to the course planner.\n" << endl;

    while (true) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit\n" << endl;
        cout << "What would you like to do? " << endl;

        string choice;
        getline(cin, choice);
        choice = Trim(choice);

        if (choice == "1") {
            cout << "Enter the file name to load: \n" << endl;
            string filename;
            getline(cin, filename);
            filename = Trim(filename);

            if (LoadCourses(filename, courseTable)) {
                dataLoaded = true;
            }
            else {
                dataLoaded = false;
            }

        }
        else if (choice == "2") {
            if (!dataLoaded) {
                cout << "Please load data first using option 1.\n" << endl;
            }
            else {
                PrintCourseList(courseTable);
            }

        }
        else if (choice == "3") {
            if (!dataLoaded) {
                cout << "Please load data first using option 1.\n" << endl;
            }
            else {
                cout << "\nWhat course do you want to know about? " << endl;
                string courseNum;
                getline(cin, courseNum);
                courseNum = Trim(courseNum);
                PrintCourseInfo(courseTable, courseNum);
            }

        }
        else if (choice == "9") {
            cout << "Thank you for using the course planner!" << endl;
            break;

        }
        else {
            cout << choice << " is not a valid option.\n" << endl;
        }
    }
}

// ===============================
// MAIN FUNCTION
// ===============================

int main() {
    DisplayMenu();
    return 0;
}