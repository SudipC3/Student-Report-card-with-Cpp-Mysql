#include <iostream>
#include <mysql.h>
#include <sstream>
#include <windows.h>
#include <iomanip> // for formatting
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PASSWORD = "your_password";
const char* DATABASE = "mydb";

class Student {
private:
    string name, rollNo, grade;
    float avg;

public:
    Student(string n, string r, float a = 0.0, string g = "")
        : name(n), rollNo(r), avg(a), grade(g) {}

    string getName() const { return name; }
    string getRollNo() const { return rollNo; }
    float getAvg() const { return avg; }
    string getGrade() const { return grade; }

    void setAvg(float a) { avg = a; }
    void setGrade(string g) { grade = g; }
};

string calculateGrade(float avg) {
    if (avg >= 90) return "A+";
    if (avg >= 80) return "A";
    if (avg >= 70) return "B+";
    if (avg >= 60) return "B";
    if (avg >= 50) return "C";
    if (avg >= 40) return "D";
    return "F";
}

void insertStudent(MYSQL* conn, const Student& s) {
    stringstream query;
    query << "INSERT INTO Student (RollNo, Name, Avg, Grade) VALUES ('"
          << s.getRollNo() << "', '" << s.getName() << "', "
          << s.getAvg() << ", '" << s.getGrade() << "')";

    if (mysql_query(conn, query.str().c_str())) {
        cerr << "Insert Error: " << mysql_error(conn) << endl;
    }
}

void updateAndShowReport(MYSQL* conn) {
    string rollNo;
    int marks[3];

    cout << "Enter Roll No: ";
    cin >> rollNo;

    for (int i = 0; i < 3; ++i) {
        cout << "Enter marks for Subject " << (i + 1) << ": ";
        while (!(cin >> marks[i]) || marks[i] < 0 || marks[i] > 100) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Re-enter: ";
        }
    }

    float avg = (marks[0] + marks[1] + marks[2]) / 3.0f;
    string grade = calculateGrade(avg);

    stringstream update;
    update << "UPDATE Student SET Avg = " << avg << ", Grade = '" << grade
           << "' WHERE RollNo = '" << rollNo << "'";

    if (mysql_query(conn, update.str().c_str())) {
        cerr << "Update Error: " << mysql_error(conn) << endl;
        return;
    }

    stringstream select;
    select << "SELECT * FROM Student WHERE RollNo = '" << rollNo << "'";
    if (mysql_query(conn, select.str().c_str())) {
        cerr << "Select Error: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    if (res) {
        cout << "\nReport Card:\n";
        cout << left << setw(12) << "RollNo"
             << setw(20) << "Name"
             << setw(10) << "Avg"
             << setw(8) << "Grade" << endl;
        cout << "---------------------------------------------\n";

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(12) << row[0]
                 << setw(20) << row[1]
                 << setw(10) << row[2]
                 << setw(8) << row[3] << endl;
        }

        mysql_free_result(res);
    } else {
        cerr << "Result Error: " << mysql_error(conn) << endl;
    }
}

int main() {
    MYSQL* conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0)) {
        cerr << "Connection Failed: " << mysql_error(conn) << endl;
        return 1;
    }

    cout << "Connected to Database.\n";

    // Initial Insert (you may skip if already present)
    Student s1("Ali", "ab123");
    Student s2("Ahmad", "bc234");
    Student s3("Kabeer", "cd345");
    insertStudent(conn, s1);
    insertStudent(conn, s2);
    insertStudent(conn, s3);

    // Menu loop
    int choice;
    do {
        cout << "\n==== Student Report Card System ====\n";
        cout << "1. Generate Report Card\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                updateAndShowReport(conn);
                break;
            case 2:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 2);

    mysql_close(conn);
    return 0;
}
