#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <unistd.h>
typedef long long int lli;
using namespace std;
class Student;

class Date
{
    int day;
    int month;
    int year;

public:
    Date(int dd = 0, int mm = 0, int yy = 0) : day{dd}, month{mm}, year{yy} {}
    void print()
    {
        if (day <= 9)
            cout << "0";
        cout << day << "/";
        if (month <= 9)
            cout << "0";
        cout << month << "/";
        cout << year;
    }
};

class Person
{
public:
    string name;
    string address;
    string phoneNumber;
    virtual void print() = 0;
    virtual ~Person() {}
    Person(string n = "NULL", string add = "NULL", string pn = "NULL") : name{n}, address{add}, phoneNumber{pn} {}
};
/*
    Generalizationa as follows:
    Teacher---->Person<----Student
*/
class Student : public Person
{
public:
    string eRoll;
    int batchId;
    void print()
    {
        cout << "\nSTUDENT DETAILS";
        cout << "\nEnrolment Number: " << eRoll;
        cout << "\nName: " << name;
        cout << "\nAddress: " << address;
        cout << "\nContact Number: " << phoneNumber;
        cout << "\nBatch: " << batchId;
    }
    Student(string er = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL", int bId = 0) : Person{n, add, pn}, eRoll{er}, batchId{bId} {}
};
class Teacher : public Person
{
public:
    string teacherId;
    string subject;
    vector<int> batchIds;
    bool vaccined;
    void print()
    {
        cout << "\nTEACHER DETAILS";
        cout << "\nFaculty ID: " << teacherId;
        cout << "\nSubject: " << subject;
        cout << "\nName: " << name;
        cout << "\nAddress: " << address;
        cout << "\nContact Number: " << phoneNumber;
        cout << "\nBatch Ids: ";
        for (int i = 0; i < batchIds.size(); i++)
            cout << batchIds[i] << " ";
        cout << endl;

        if (vaccined)
            cout
                << "\nCOVID-19 immune";
        else
            cout << "\nNOT VACCINATED for COVID-19 yet";
    }
    Teacher(string tId = "NULL", string sub = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL", bool bl = false, vector<int> bIds = {}) : Person{n, add, pn}, teacherId{tId}, vaccined{bl}, subject{sub}, batchIds{bIds} {}
};

class Batch
{
public:
    int batchId;
    vector<Student *> student;
    vector<Teacher *> teacher;
    Batch(int b, vector<Student *> s = {}, vector<Teacher *> t = {})
    {
        batchId = b;
        student = s;
        teacher = t;
    }
    int addStudent(string er = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL")
    {
        Student *s = new Student(er, n, add, pn, batchId);
        student.push_back(s);
        return student.size();
    }
    int addStudent(Student *s)
    {
        student.push_back(s);
        return student.size();
    }
    int addTeacher(string tId = "NULL", string sub = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL", bool bl = false, vector<int> batchIds = {})
    {
        Teacher *t = new Teacher(tId, sub, n, add, pn, bl, batchIds);
        teacher.push_back(t);
        return teacher.size();
    }
    int addTeacher(Teacher *s)
    {
        teacher.push_back(s);
        return teacher.size();
    }
};

class Patient
{
    Student *student;
    Teacher *teacher;
    Date positive;

public:
    Patient()
    {
        student = nullptr;
        teacher = nullptr;
        positive = Date();
    }
    Patient(Teacher t, int dd, int mm, int yy) : positive{Date(dd, mm, yy)}
    {
        teacher = new Teacher(t);
    }
    Patient(Student s, int dd, int mm, int yy) : positive{Date(dd, mm, yy)}
    {
        student = new Student(s);
    }

    void print()
    {
        if (student != nullptr)
            student->print();
        else
            teacher->print();
        cout << "\nTested positive on: ";
        positive.print();
    }
};

class Admin
{
public:
    int adminId;
    string name;
    string password;

    Admin(int aId = 100, string n = "NULL", string pwd = "JIIT@65")
    {
        adminId = aId;
        name = n;
        pwd = password;
    }
    bool storeAdminData()
    {
        if (adminId == 0)
            return false;
        ofstream out("ADMIN.txt", ios::app | ios::binary);
        if (!out)
            return false;

        char line[100] = "\0";
        strcat(line, to_string(adminId).c_str());
        strcat(line, "&");
        strcat(line, password.c_str());
        strcat(line, "&");
        strcat(line, name.c_str());
        strcat(line, "\n");

        out.write(line, sizeof(*line));
        out.close();
        return true;
    }
};
void titleBar()
{
    system("cls");
    cout << "\n\t\t\t\t\t\t      -----------------------------------------";
    cout << "\n\t\t\t\t\t\t\t\tJIIT COVID-19 TRACKING";
    cout << "\n\t\t\t\t\t\t      -----------------------------------------";
}
int mainPage()
{
    titleBar();
    cout << "\n\t\t\t\t\t\t\t\t1. STUDENT LOGIN";
    cout << "\n\t\t\t\t\t\t\t\t2. TEACHER LOGIN";
    cout << "\n\t\t\t\t\t\t\t\t3. ADMIN LOGIN";
    cout << "\n\t\t\t\t\t\t\t\t0. ANY OTHER TO EXIT";
    int n;
    cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
    cout << "\n\t\t\t\t\t\t\t\tINPUT: ";
    cin >> n;
    return n;
}

string search(string file, lli id, string pass)
{
    ifstream in(file, ios::in);
    if (!in)
    {
        cout << "\nUnable to open a required file!\n";
        return "-1";
    }

    while (!in.eof())
    {
        char data[100] = "";
        in.getline(data, 100, '\n');
        int len = strlen(data);

        char tempId[8], tempPass[21];
        int i = 0;
        for (; data[i] != '&'; i++)
        {
            tempId[i] = data[i];
        }
        tempId[i++] = '\0';
        if (strcmp(tempId, to_string(id).c_str()) == 0)
        {
            int j = 0;
            for (; data[i] != '&'; i++, j++)
                tempPass[j] = data[i];

            tempPass[j++] = '\0';
            if (strcmp(tempPass, pass.c_str()) == 0)
            {
                cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                cout << "\n\t\t\t\t\t\t\t\t LOGIN SUCCESSFULL";
                cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                sleep(1);
                return tempId;
            }
            else
            {
                cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                cout << "\n\t\t\t\t\t\t\t\t INCORRECT PASSWORD";
                cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                return "-1";
            }
        }
    }
    cout << "\n\t\t\t\t\t\t      -----------------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t     INCORRECT ID";
    cout << "\n\t\t\t\t\t\t      -----------------------------------------";
    return "-1";
}

string loginPage(string str)
{
    titleBar();
    lli id;
    string pwd;
    cout << "\n\n\t\t\t\t\t\t\tENTER " << str << " ID: ";
    cin >> id;
    cout << "\n\t\t\t\t\t\t\tENTER PASSWORD: ";
    cin >> pwd;

    str += ".txt";
    return search(str, id, pwd);
}
Student rhythm("992061", "Siddhart Malhotra", "Noida-69", "993873723", 65);
Student sid("992062", "Rhthm Shandlya", "Noida-69", "993873723", 65);
Student anshu("992063", "Anshuman Tyagi", "Noida-69", "993873723", 65);
vector<Student> studs = {rhythm, sid, anshu};

int main()
{
MAIN:
    int n;
    do
    {
        int n = mainPage();
        if (n == 1)
        {
        STUDENT_1:
            string str = loginPage("STUDENT");
            if (str != "-1")
            {
            }
            else
            {
            STUDENT_2:
                cout << "\n\t\t\t\t\t\t\t\t0. BACK TO MAIN SCREEN";
                cout << "\n\t\t\t\t\t\t\t\t1. RETRY LOGIN";
                int m;
                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\t\tINPUT: ";
                cin >> m;
                if (m == 0)
                {
                    goto MAIN;
                }
                else if (m == 1)
                {
                    goto STUDENT_1;
                }
                else
                {
                    goto STUDENT_2;
                }
            }
        }
        else if (n == 2)
        {
        TEACHER_1:
            string str = loginPage("TEACHER");
            if (str != "-1")
            {
            }
            else
            {
            TEACHER_2:
                cout << "\n\t\t\t\t\t\t\t\t0. BACK TO MAIN SCREEN";
                cout << "\n\t\t\t\t\t\t\t\t1. RETRY LOGIN";
                int m;
                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\t\tINPUT: ";
                cin >> m;
                if (m == 0)
                {
                    goto MAIN;
                }
                else if (m == 1)
                {
                    goto TEACHER_1;
                }
                else
                {
                    goto TEACHER_2;
                }
            }
        }
        else if (n == 3)
        {
        ADMIN_1:
            string str = loginPage("ADMIN");
            if (str != "-1")
            {
            }
            else
            {
            ADMIN_2:
                cout << "\n\t\t\t\t\t\t\t\t0. BACK TO MAIN SCREEN";
                cout << "\n\t\t\t\t\t\t\t\t1. RETRY LOGIN";
                int m;
                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\t\tINPUT: ";
                cin >> m;
                if (m == 0)
                {
                    goto MAIN;
                }
                else if (m == 1)
                {
                    goto ADMIN_1;
                }
                else
                {
                    goto ADMIN_2;
                }
            }
        }
        else
        {
            cout << "\n\t\t\t\t\t\t      -----------------------------------------";
            cout << "\n\t\t\t\t\t\t\t\t  PROGRAM TERMINATED";
            cout << "\n\t\t\t\t\t\t      -----------------------------------------";
        }
    } while (n == 1 || n == 2 || n == 3);
    return 0;
}