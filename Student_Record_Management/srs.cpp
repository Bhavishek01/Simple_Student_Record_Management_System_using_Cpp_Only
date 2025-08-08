#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

const string subjects[] = {"Mathematics", "Physics", "Chemistry", "Biology", "English"};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class User {
protected:
    string name;
    string id;
    string password;

public:
    virtual void signup() = 0;
    virtual bool login() = 0;

    void setId(const string& userId) 
	{
        id = userId;
    }
    
    string getId() 
	const {
        return id;
    }

    void setPassword(const string& pass) {
        password = pass;
    }
    string getPassword() const {
        return password;
    }
};

class Teacher : public User {
private:
    string subject;

public:
    bool login() {
        system("CLS");
        string inputId, inputPassword;
        cout << "\t\tTeacher Portal - Login\n" << endl;
        cout << "\nEnter Teacher ID: ";
        cin >> inputId;
        cout << "\nEnter Password: ";
        cin >> inputPassword;

        ifstream file("teachers.txt");
        while (file >> name >> id >> password >> subject) {
            if (id == inputId && password == inputPassword) {
                return true;
            }
        }
        return false;
    }

    void setSubject(const string& sub) {
        subject = sub;
    }

    string getSubject() const {
        return subject;
    }

void enterMarks() {
    system("CLS");
    cout << "\t\tTeacher Portal - Marks Entry\n" << endl;

    ifstream studentFile("students.txt");
    if (!studentFile) {
        cout << "No registered students found.\n";
        return;
    }

    string studentName, studentId, phone, guardian;
    int z = 4;
    int y = 5;
    gotoxy(5, z);
    cout << "Student ID";
    gotoxy(20, z);
    cout << "Student Name";
    gotoxy(40, z);
    cout << "Marks";

    ofstream marksFile("marks.txt", ios::app);

    while (studentFile >> studentName >> studentId >> password >> phone >> guardian) {
        gotoxy(5, y);
        cout << studentId;
        gotoxy(20, y);
        cout << studentName;

        int marks;
        while (true) {
            gotoxy(40, y);
            cout << " ";
            cin >> marks;

            if (marks >= 0 && marks <= 100) {
                marksFile << studentId << " " << subject << " " << marks << endl;
                break;  // Exit the loop if the marks are valid
            } 
			else {
                gotoxy(40, y);
                cout << "                         ";  // Clear the invalid input
            }
        }
        y++;
    }

    marksFile.close();
    studentFile.close();
    cout << "\nMarks entered successfully!" << endl;
}


    void signup() {
        cout << "heeeeeeeeeheeeeeehe";
    }
};

class Student : public User {
private:
    string phoneNumber;
    string guardianName;

public:
    bool login() {
        system("CLS");
        string inputId, inputPassword;
        cout << "\t\tStudent Portal - Login\n" << endl;
        cout << "\nEnter Student ID: ";
        cin >> inputId;
        cout << "\nEnter Password: ";
        cin >> inputPassword;

        ifstream file("students.txt");
        while (file >> name >> id >> password >> phoneNumber >> guardianName) {
            if (id == inputId && password == inputPassword) {
                return true;
            }
        }
        return false;
    }

    void viewDetails() {
        system("CLS");
        cout << "\t\tStudent Portal - Student Details\n" << endl;
        cout << "\nStudent Name: " << name << endl;
        cout << "\nStudent ID: " << id << endl;
        cout << "\nPhone Number: " << phoneNumber << endl;
        cout << "\nGuardian Name: " << guardianName << endl;
    }

    void viewResults() {
        system("CLS");
        cout << "\t\tStudent Portal - View Results\n" << endl;
        cout << "\nResults for Student ID: " << id << endl;
        ifstream marksFile("marks.txt");
        string studentId, subject;
        int marks;
        float avg;
        bool found = false;

        while (marksFile >> studentId >> subject >> marks) {
            if (studentId == id) {
            	avg = avg + marks;
                cout << "Subject: " << subject << ", Marks: " << marks << endl;
                found = true;
                
            }
        }
        if (!found) {
            cout << "\nNo results found for this student." << endl;
        }
        
        cout << "\nTotal: "<<avg<<endl;
        cout<<"\nPercentage: "<< avg/5 << " %"<<endl;
        
        if(avg/5 < 45)
        {
        	cout<<"\nFAILED"<<endl;
		}
		else
		{
			cout<<"\nPASSED\n\n\n"<<endl;
		}
    }

    void signup() {
        cout << "\nSignup is not available for students. Contact the faculty to register.\n";
    }
};

class FacultyMember : public User {
public:
    void signup() {
        cout << "no no no no no \n";
    }
    
    void viewAllResults() {
    system("CLS");
    cout << "\t\tFaculty Portal - View All Results\n" << endl;

    ifstream studentFile("students.txt");
    if (!studentFile) {
        cout << "No student data found.\n";
        return;
    }

    string name, id, password, phone, guardian;
    cout << "\nResults:\n";
    cout << "--------------------------------------------\n";
    cout << "Student ID\tName\t\tPercentage\tStatus\n";
    cout << "--------------------------------------------\n";

    // Iterate over each student in the student file
    while (studentFile >> name >> id >> password >> phone >> guardian) {
        ifstream marksFile("marks.txt");
        if (!marksFile) {
            cout << "No marks data found.\n";
            studentFile.close();
            return;
        }

        string studentId, subject;
        int marks, totalMarks = 0, subjectCount = 0;

        // Calculate total marks and subject count for the current student
        while (marksFile >> studentId >> subject >> marks) {
            if (studentId == id) {
                totalMarks += marks;
                subjectCount++;
            }
        }

        marksFile.close();

        // Calculate the percentage
        float percentage = subjectCount > 0 ? (totalMarks / (float)subjectCount) : 0;

        // Display the result for the current student
        cout << id << "\t\t" << name << "\t\t" << percentage << "%\t\t";
        if (percentage < 45.0) {
            cout << "FAILED\n";
        } else {
            cout << "PASSED\n";
        }
    }

    cout << "--------------------------------------------\n";
    studentFile.close();
}

    bool login() {
        system("CLS");
        string inputId, inputPassword;
        cout << "\t\tFaculty Portal - Login\n" << endl;
        cout << "\nEnter Faculty ID: ";
        cin >> inputId;
        cout << "\nEnter Password: ";
        cin >> inputPassword;

        return inputId == "kantipur" && inputPassword == "kantipur";
    }

void registerTeacher() {
    system("CLS");
    Teacher teacher;
    string name, id, password;
    bool valid = false;

cout << "\t\tFaculty Portal - Register Teacher\n" << endl;

while (!valid) {
    cout << "\nEnter Teacher Name (alphabets only): ";
    cin >> name;

    valid = true; // Assume valid unless proven otherwise

    for (size_t i = 0; i < name.length(); ++i) { // Loop through the string
        if (!isalpha(static_cast<unsigned char>(name[i]))) { // Check if the character is not alphabetic
            valid = false; // Set valid to false if any non-alphabet character is found
            break;
        }
    }

    if (!valid) {
        cout << "Invalid entry! Please enter only alphabets." << endl;
    } else {
        cout << "Name is valid." << endl;
    }
}


    cout << "\nEnter Teacher ID: ";
    cin >> id;
    teacher.setId(id);

    cout << "\nEnter Password: ";
    cin >> password;
    teacher.setPassword(password);

    cout << "\nSelect Subject from the following list:\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << subjects[i] << endl;
    }
    int subjectChoice;
    cin >> subjectChoice;

    if (subjectChoice < 1 || subjectChoice > 5) {
        cout << "\nInvalid subject choice.\n";
        return;
    }
    teacher.setSubject(subjects[subjectChoice - 1]);

    ofstream fileOut("teachers.txt", ios::app);
    fileOut << name << " " << teacher.getId() << " " << teacher.getPassword() << " " << teacher.getSubject() << endl;
    fileOut.close();
    cout << "\nTeacher registered successfully!" << endl;
}

void registerStudent() 
{
    system("CLS");
    Student student;
    string name, id, password, phone, guardian;
    bool valid = false;

cout << "\t\tFaculty Portal - Student Teacher\n" << endl;

while (!valid) {
    cout << "\nEnter Student Name (alphabets only): ";
    cin >> name;

    valid = true; // Assume valid unless proven otherwise

    for (size_t i = 0; i < name.length(); ++i) { // Loop through the string
        if (!isalpha(static_cast<unsigned char>(name[i]))) { // Check if the character is not alphabetic
            valid = false; // Set valid to false if any non-alphabet character is found
            break;
        }
    }

    if (!valid) {
        cout << "Invalid entry! Please enter only alphabets." << endl;
    } else {
        cout << "Name is valid." << endl;
    }
}

    cout << "\nEnter Student ID: ";
    cin >> id;
    student.setId(id);

    cout << "\nEnter Password: ";
    cin >> password;
    student.setPassword(password);
    
    valid = false;
    
while (!valid) {
	
    cout << "\nEnter phhone : ";
    cin >> phone;

    valid = true; // Assume valid unless proven otherwise

    for (size_t i = 0; i < phone.length(); ++i) { // Loop through the string
        if (!isdigit(static_cast<unsigned char>(phone[i]))) { // Check if the character is not alphabetic
            valid = false; // Set valid to false if any non-alphabet character is found
            break;
        }
    }

    if (!valid) 
	{
        cout << "Invalid entry! Please enter only number." << endl;
    } else {
        cout << "Phone numnber is valid." << endl;
    }
}

    valid = false;

while (!valid) {
    cout << "\nEnter Guardian Name (alphabets only): ";
    cin >> guardian;

    valid = true; // Assume valid unless proven otherwise

    for (size_t i = 0; i < guardian.length(); ++i) { // Loop through the string
        if (!isalpha(static_cast<unsigned char>(guardian[i]))) { // Check if the character is not alphabetic
            valid = false; // Set valid to false if any non-alphabet character is found
            break;
        }
    }

    if (!valid) {
        cout << "Invalid entry! Please enter only alphabets." << endl;
    } else {
        cout << "Name is valid." << endl;
    }
}

    ofstream fileOut("students.txt", ios::app);
    fileOut << name << " " << student.getId() << " " << student.getPassword() << " " << phone << " " << guardian << endl;
    fileOut.close();
    cout << "\nStudent registered successfully!" << endl;
}

    void editStudentDetails() {
        system("CLS");
        cout << "\t\tFaculty Portal - Edit Student Details\n" << endl;

        string studentId, newName, newPhone, newGuardian;
        cout << "Enter Student ID: ";
        cin >> studentId;

        ifstream inputFile("students.txt");
        ofstream tempFile("temp.txt");

        string name, id, password, phone, guardian;
        bool found = false;

        while (inputFile >> name >> id >> password >> phone >> guardian) {
            if (id == studentId) {
                cout << "Enter New Name: ";
                cin >> newName;
                cout << "Enter New Phone Number: ";
                cin >> newPhone;
                cout << "Enter New Guardian Name: ";
                cin >> newGuardian;
                tempFile << newName << " " << id << " " << password << " " << newPhone << " " << newGuardian << endl;
                found = true;
            } else {
                tempFile << name << " " << id << " " << password << " " << phone << " " << guardian << endl;
            }
        }

        inputFile.close();
        tempFile.close();
        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found) {
            cout << "Student details updated successfully.\n";
        } else {
            cout << "Student not found.\n";
        }
    }

    void searchStudent() {
        system("CLS");
        cout << "\t\tFaculty Portal - Search Student\n" << endl;

        string studentId;
        cout << "Enter Student ID: ";
        cin >> studentId;

        ifstream inputFile("students.txt");
        string name, id, password, phone, guardian;
        bool found = false;

        while (inputFile >> name >> id >> password >> phone >> guardian) {
            if (id == studentId) {
                cout << "Name: " << name << endl;
                cout << "Phone: " << phone << endl;
                cout << "Guardian: " << guardian << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Student not found.\n";
        }
    }
};

int main() {
    while (true) {
        system("CLS");
        cout << "\t\tSchool Record System\n" << endl;
        cout << "1. Faculty Login\n";
        cout << "2. Teacher Login\n";
//        cout << "3. Student Login\n";
        cout << "0. Exit\n";
        cout << "\nEnter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            FacultyMember faculty;
            if (faculty.login()) {
                while (true) {
    system("CLS");
    cout << "\t\tFaculty Portal\n" << endl;
    cout << "1. Register Teacher\n";
    cout << "2. Register Student\n";
    cout << "3. Edit Student Details\n";
    cout << "4. Search Student\n";
    cout << "5. View All Results\n"; // New option added
    cout << "0. Logout\n";
    cout << "\nEnter your choice: ";
    int facultyChoice;
    cin >> facultyChoice;

    if (facultyChoice == 1) {
        faculty.registerTeacher();
    } else if (facultyChoice == 2) {
        faculty.registerStudent();
    } else if (facultyChoice == 3) {
        faculty.editStudentDetails();
    } else if (facultyChoice == 4) {
        faculty.searchStudent();
    } else if (facultyChoice == 5) { // Handle the new option
        faculty.viewAllResults();
    } else if (facultyChoice == 0) {
        break;
    } else {
        cout << "\nInvalid choice. Please try again.\n";
    }
    system("pause");
}

            } else {
                cout << "Invalid credentials.\n";
            }
        } 
		else if (choice == 2) {
            Teacher teacher;
            if (teacher.login()) {
                while (true) {
                    system("CLS");
                    cout << "\t\tTeacher Portal\n" << endl;
                    cout << "1. Enter Marks\n";
                    cout << "0. Logout\n";
                    cout << "\nEnter your choice: ";
                    int teacherChoice;
                    cin >> teacherChoice;

                    if (teacherChoice == 1) {
                        teacher.enterMarks();
                    } else if (teacherChoice == 0) {
                        break;
                    } else {
                        cout << "\nInvalid choice. Please try again.\n";
                    }
                    system("pause");
                }
            } else {
                cout << "Invalid credentials.\n";
            }
        } 
		else if (choice == 0) {
            cout << "Exiting the program.\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
        system("pause");
    }
    return 0;
}

