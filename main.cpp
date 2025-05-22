#include <iostream>
#include <iomanip>
using namespace std;

const int NUM_STUDENTS = 3;
const int NUM_SUBJECTS = 3;

class FullName {
private:
    string firstName;
    string middleName;
    string lastName;

public:
    void readData() {
        cout << "First Name : ";
        cin >> firstName;
        cout << "Middle Name: ";
        cin >> middleName;
        cout << "Last Name  : ";
        cin >> lastName;
    }

    string getFullName() const {
        return firstName + " " + middleName + " " + lastName;
    }
};

class Subject {
private:
    string name;
    float grade;

public:
    void setName(const string& n) { name = n; }

    void readGrade() {
        cout << "Enter grade for " << name << ": ";
        cin >> grade;
    }

    void readGrade(float g) {
        grade = g;
    }

    string getName() const { return name; }
    float getGrade() const { return grade; }
};

class Person {
protected:
    string universityID;
    FullName name;

public:
    virtual void readData() {
        do {
            cout << "University ID (12 digits): ";
            cin >> universityID;
        } while (universityID.length() != 12);

        name.readData();
    }

    virtual void printData() const {
        cout << "University ID: " << universityID << endl;
        cout << "Full Name    : " << name.getFullName() << endl;
    }

    virtual ~Person() {}
};

class Student : public Person {
private:
    Subject subjects[NUM_SUBJECTS];
    float average;

public:
    void readData() override {
        Person::readData();

        string subjectNames[NUM_SUBJECTS] = {"Math", "Physics", "Programming"};
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            subjects[i].setName(subjectNames[i]);
            subjects[i].readGrade();
        }

        calculateAverage();
    }

    void calculateAverage() {
        float sum = 0;
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            sum += subjects[i].getGrade();
        }
        average = sum / NUM_SUBJECTS;
    }

    void printData() const override {
        Person::printData();
        cout << "Grades:\n";
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            cout << " - " << subjects[i].getName() << ": "
                 << fixed << setprecision(2) << subjects[i].getGrade() << endl;
        }
        cout << "Average: " << fixed << setprecision(2) << average << endl;
        cout << "-----------------------------\n";
    }
};

int main() {
    Person* students[NUM_STUDENTS];
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        cout << "Enter data for student #" << i + 1 << ":\n";
        students[i] = new Student();
        students[i]->readData();
    }

    cout << "\n===== Student Information =====\n";
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        students[i]->printData();
        delete students[i];
    }

    return 0;
}
