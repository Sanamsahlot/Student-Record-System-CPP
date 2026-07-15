#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Student structure to hold temporary memory data
struct Student {
    int rollNumber;
    string name;
    double marks;
};

const string FILE_NAME = "students.txt";

// Helper function to clear input buffer
void clearBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// 1. Add student record to text file
void addStudentRecord() {
    ofstream outFile(FILE_NAME, ios::app);
    if (!outFile) {
        cout << "Error: Could not open database file!" << endl;
        return;
    }

    Student temp;
    cout << "\n--- Add New Student ---" << endl;
    
    cout << "Enter Roll Number: ";
    while (!(cin >> temp.rollNumber)) {
        cout << "Invalid input! Please enter an integer Roll Number: ";
        clearBuffer();
    }
    clearBuffer();

    cout << "Enter Student Name: ";
    getline(cin, temp.name);

    cout << "Enter Marks: ";
    while (!(cin >> temp.marks)) {
        cout << "Invalid input! Please enter decimal/integer Marks: ";
        clearBuffer();
    }

    // Saving data as plain text with tabs as separators
    outFile << temp.rollNumber << "\t" << temp.name << "\t" << temp.marks << endl;
    outFile.close();
    cout << "Record added successfully!" << endl;
}

// 2. Display all records
void displayAllRecords() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\nDatabase is empty! No records found." << endl;
        return;
    }

    Student temp;
    cout << "\n==================================================" << endl;
    cout << left << setw(15) << "Roll No" << setw(25) << "Name" << setw(10) << "Marks" << endl;
    cout << "==================================================" << endl;

    bool recordsExist = false;
    // Reading plain text file line by line
    while (inFile >> temp.rollNumber) {
        inFile.ignore(); // skip tab
        getline(inFile, temp.name, '\t'); // read name until next tab
        inFile >> temp.marks;
        
        cout << left << setw(15) << temp.rollNumber 
             << setw(25) << temp.name 
             << setw(10) << temp.marks << endl;
        recordsExist = true;
    }
    inFile.close();
    
    if (!recordsExist) {
        cout << "No records found in the database." << endl;
    }
    cout << "==================================================" << endl;
}

// 3. Search a student by Roll Number
void searchStudentRecord() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\nDatabase is empty! No records found to search." << endl;
        return;
    }

    int searchRoll;
    cout << "\nEnter Roll Number to Search: ";
    cin >> searchRoll;

    Student temp;
    bool found = false;

    while (inFile >> temp.rollNumber) {
        inFile.ignore();
        getline(inFile, temp.name, '\t');
        inFile >> temp.marks;

        if (temp.rollNumber == searchRoll) {
            cout << "\n--- Record Found ---" << endl;
            cout << left << setw(15) << "Roll No" << setw(25) << "Name" << setw(10) << "Marks" << endl;
            cout << "--------------------------------------------------" << endl;
            cout << left << setw(15) << temp.rollNumber 
                 << setw(25) << temp.name 
                 << setw(10) << temp.marks << endl;
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "Student with Roll Number " << searchRoll << " not found." << endl;
    }
}

// 4. Modify student record
void modifyStudentRecord() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\nDatabase is empty! No records found to modify." << endl;
        return;
    }

    int searchRoll;
    cout << "\nEnter Roll Number to Modify: ";
    cin >> searchRoll;

    ofstream tempFile("temp.txt");
    Student temp;
    bool found = false;

    while (inFile >> temp.rollNumber) {
        inFile.ignore();
        getline(inFile, temp.name, '\t');
        inFile >> temp.marks;

        if (temp.rollNumber == searchRoll) {
            found = true;
            cout << "\nCurrent Details - Name: " << temp.name << ", Marks: " << temp.marks << endl;
            
            cout << "\nEnter New Name: ";
            clearBuffer();
            getline(cin, temp.name);
            
            cout << "Enter New Marks: ";
            while (!(cin >> temp.marks)) {
                cout << "Invalid input! Enter correct Marks: ";
                clearBuffer();
            }
            cout << "Record modified successfully!" << endl;
        }
        tempFile << temp.rollNumber << "\t" << temp.name << "\t" << temp.marks << endl;
    }

    inFile.close();
    tempFile.close();

    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (!found) {
        cout << "Student with Roll Number " << searchRoll << " not found." << endl;
    }
}

// 5. Delete student record
void deleteStudentRecord() {
    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "\nDatabase is empty! No records found to delete." << endl;
        return;
    }

    int searchRoll;
    cout << "\nEnter Roll Number to Delete: ";
    cin >> searchRoll;

    ofstream tempFile("temp.txt");
    Student temp;
    bool found = false;

    while (inFile >> temp.rollNumber) {
        inFile.ignore();
        getline(inFile, temp.name, '\t');
        inFile >> temp.marks;

        if (temp.rollNumber == searchRoll) {
            found = true; // Skip writing this record to temp.txt (Deletes it)
        } else {
            tempFile << temp.rollNumber << "\t" << temp.name << "\t" << temp.marks << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (found) {
        cout << "Record deleted successfully!" << endl;
    } else {
        cout << "Student with Roll Number " << searchRoll << " not found." << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n==========================================" << endl;
        cout << "        STUDENT RECORD SYSTEM             " << endl;
        cout << "==========================================" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Display All Student Records" << endl;
        cout << "3. Search Student Record" << endl;
        cout << "4. Modify Student Record" << endl;
        cout << "5. Delete Student Record" << endl;
        cout << "6. Exit Application" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        if (choice == 6) {
            cout << "\nExiting Student Record System. Goodbye!" << endl;
            break;
        }

        switch (choice) {
            case 1:
                addStudentRecord();
                break;
            case 2:
                displayAllRecords();
                break;
            case 3:
                searchStudentRecord();
                break;
            case 4:
                modifyStudentRecord();
                break;
            case 5:
                deleteStudentRecord();
                break;
            default:
                cout << "Invalid Selection! Please choose between 1 and 6." << endl;
        }
    }
    return 0;
}