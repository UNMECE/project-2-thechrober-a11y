#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Student {
protected:
    string firstName;
    string lastName;
    double gpa;
    int gradYear;
    string gradSemester;
    int enrolledYear;
    string enrolledSemester;
    string level;

public:
    Student() { //default values
        firstName = "None";
        lastName = "None";
        gpa = 0.0;
        gradYear = 0;
        gradSemester = "None";
        enrolledYear = 0;
        enrolledSemester = "None";
        level = "undergrad";
    }

    virtual ~Student() {}

    void setName(const string &first, const string &last) { firstName = first; lastName = last; }
    void setGPA(double g) { gpa = g; }
    void setGradInfo(int year, const string &sem) { gradYear = year; gradSemester = sem; }
    void setEnrollInfo(int year, const string &sem) { enrolledYear = year; enrolledSemester = sem; }
    void setLevel(const string &lvl) { level = lvl; }

    virtual void printToFile(ofstream &out) const {
        out << "Name: " << firstName << " " << lastName << "\n";
        out << "GPA: " << gpa << "\n";
        out << "Graduation: " << gradSemester << " " << gradYear << "\n";
        out << "Enrolled: " << enrolledSemester << " " << enrolledYear << "\n";
        out << "Level: " << level << "\n";
    }
};
//art student class
class Art_Student : public Student {
private:
    string artEmphasis;

public:
    Art_Student() : Student() { artEmphasis = "Art Studio"; }
    ~Art_Student() override {}

    void setEmphasis(const string &e) { artEmphasis = e; }

    void printToFile(ofstream &out) const override {
        out << "===== Art Student =====\n";
        Student::printToFile(out);
        out << "Art Emphasis: " << artEmphasis << "\n\n";
    }
};
//phys student class
class Physics_Student : public Student {
private:
    string concentration;

public:
    Physics_Student() : Student() { concentration = "Biophysics"; }
    ~Physics_Student() override {}

    void setConcentration(const string &c) { concentration = c; }

    void printToFile(ofstream &out) const override {
        out << "===== Physics Student =====\n";
        Student::printToFile(out);
        out << "Concentration: " << concentration << "\n\n";
    }
};
//check to force number values if strings are entered
double getDouble(const string &prompt) {
    string input;
    double value;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            value = stod(input);
            break;
        } catch (...) {
            cout << "Invalid input. Please enter a number.\n";
        }
    }
    return value;
}

int getInt(const string &prompt) {
    string input;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            value = stoi(input);
            break;
        } catch (...) {
            cout << "Invalid input. Please enter an integer.\n";
        }
    }
    return value;
}
//gets user input for appropriate field
string getString(const string &prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void inputArtStudent(Art_Student *s) {
    string first = getString("\nEnter Art Student First Name: ");
    string last = getString("Enter Last Name: ");
    s->setName(first, last);

    double gpa = getDouble("Enter GPA: ");
    s->setGPA(gpa);

    int gy = getInt("Graduation Year: ");
    string gsem = getString("Graduation Semester: ");
    s->setGradInfo(gy, gsem);

    int ey = getInt("Enrolled Year: ");
    string esem = getString("Enrolled Semester: ");
    s->setEnrollInfo(ey, esem);

    string level = getString("Level (undergrad/grad): ");
    s->setLevel(level);

    string emphasis = getString("Art Emphasis (Art Studio / Art History / Art Education): ");
    s->setEmphasis(emphasis);
}

void inputPhysicsStudent(Physics_Student *s) {
    string first = getString("\nEnter Physics Student First Name: ");
    string last = getString("Enter Last Name: ");
    s->setName(first, last);

    double gpa = getDouble("Enter GPA: ");
    s->setGPA(gpa);

    int gy = getInt("Graduation Year: ");
    string gsem = getString("Graduation Semester: ");
    s->setGradInfo(gy, gsem);

    int ey = getInt("Enrolled Year: ");
    string esem = getString("Enrolled Semester: ");
    s->setEnrollInfo(ey, esem);

    string level = getString("Level (undergrad/grad): ");
    s->setLevel(level);

    string conc = getString("Physics Concentration (Biophysics / Earth and Planetary Sciences): ");
    s->setConcentration(conc);
}

int main() {
    cout << "================ STUDENT ENTRY PROGRAM ================\n";
    cout << "If you want to stop the program early, press Ctrl+C to exit.\n";
    cout << "=======================================================\n\n";

    vector<Art_Student *> artStudents;
    vector<Physics_Student *> physicsStudents;

    for (int i = 0; i < 5; i++) {
        Art_Student *a = new Art_Student();
        cout << "\n--- Input Art Student #" << i + 1 << " ---\n";
        inputArtStudent(a);
        artStudents.push_back(a);
    }

    for (int i = 0; i < 5; i++) {
        Physics_Student *p = new Physics_Student();
        cout << "\n--- Input Physics Student #" << i + 1 << " ---\n";
        inputPhysicsStudent(p);
        physicsStudents.push_back(p);
    }

    ofstream outfile("student_info.dat");
    if (!outfile) {
        cout << "Error opening file!\n";
        return 1;
    }

    outfile << "===== STUDENT INFORMATION =====\n\n";

    for (auto s : artStudents)
        s->printToFile(outfile);

    for (auto s : physicsStudents)
        s->printToFile(outfile);

    outfile.close();
    cout << "\nStudent information written to student_info.dat\n";

    for (auto s : artStudents) delete s;
    for (auto s : physicsStudents) delete s;

    return 0;
}

