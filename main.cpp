#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unistd.h>

typedef long long int lli;
using namespace std;
class Student;

int countCases()
{
    ifstream in("POSITIVE.txt", ios::in);
    if (!in)
    {
        cout << "\nUnable to open a required file!\n";
        return -1;
    }
    int count = 0;
    while (!in.eof())
    {
        char data[30] = "";
        in.getline(data, 30, '\n');
        count++;
    }
    return count - 1;
}
int covidcase = countCases();

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
    bool vaccined;
    Date enrolmentDate;
    void print()
    {
        cout << "\n\t\t\t\t\t\t\t\t STUDENT DETAILS";
        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
        cout << "\n\t\t\t\t\t\t\tEnrolment Number: " << eRoll;
        cout << "\n\t\t\t\t\t\t\tName: " << name;
        cout << "\n\t\t\t\t\t\t\tAddress: " << address;
        cout << "\n\t\t\t\t\t\t\tContact Number: " << phoneNumber;
        cout << "\n\t\t\t\t\t\t\tBatch: " << batchId;
        cout << "\n\t\t\t\t\t\t\tDate of admission: ";
        enrolmentDate.print();
        if (vaccined)
            cout
                << "\n\t\t\t\t\t\t\tCOVID-19 immune";
        else
            cout << "\n\t\t\t\t\t\t\tNOT VACCINATED for COVID-19 yet";
    }
    void saveStudent()
    {
        /*
            Save data to file,implemented otherway round.
        */
    }
    Student(string er = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL", int bId = 0, Date d = Date()) : Person{n, add, pn}, eRoll{er}, batchId{bId}, enrolmentDate{d} {}
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
        cout << "\n\t\t\t\t\t\t\t\t TEACHER DETAILS";
        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
        cout << "\n\t\t\t\t\t\t\t\nFaculty ID: " << teacherId;
        cout << "\n\t\t\t\t\t\t\tSubject: " << subject;
        cout << "\n\t\t\t\t\t\t\tName: " << name;
        cout << "\n\t\t\t\t\t\t\tAddress: " << address;
        cout << "\n\t\t\t\t\t\t\tContact Number: " << phoneNumber;
        cout << "\n\t\t\t\t\t\t\tBatch Ids: ";
        for (int i = 0; i < batchIds.size(); i++)
            cout << batchIds[i] << " ";
        cout << endl;

        if (vaccined)
            cout << "\n\t\t\t\t\t\t\tCOVID-19 immune";
        else
            cout << "\n\t\t\t\t\t\t\tNOT VACCINATED for COVID-19 yet";
    }
    void saveTeacer()
    {
        /*
            Save data to file,implemented otherway round
        */
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

class Admin
{
public:
    string adminId;
    string name;
    string contact;

    Admin(string aId = "-1", string n = "NULL", string con = "NULL")
    {
        adminId = aId;
        name = n;
        contact = con;
    }
    bool operator==(const Admin &n) const
    {
        return adminId == n.adminId;
    }
    void print()
    {
        cout << "\n\t\t\t\t\t\t\t\t ADIMN DETAILS";
        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
        cout << "\n\t\t\t\t\t\t\t  ID : " << adminId;
        cout << "\n\t\t\t\t\t\t\t  NAME : " << name;
        cout << "\n\t\t\t\t\t\t\t  contact : " << contact;
        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
    }
    void saveAdmin()
    {
        /*
            Save data to file,implemented otherway round
        */
    }
};

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
    cout << "\n\t\t\t\t\t\t\tINPUT: ";
    cin >> n;
    return n;
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

int studentPage()
{
    titleBar();
    cout << "\n\t\t\t\t\t\t\t1. GET DETAILS";
    cout << "\n\t\t\t\t\t\t\t2. REPORT POSITIVE";
    cout << "\n\t\t\t\t\t\t\t3. COVID-19 SEARCH";
    cout << "\n\t\t\t\t\t\t\t4. NEWS AND UPDATES";
    cout << "\n\t\t\t\t\t\t\t5. BACK TO MAIN PAGE";
    cout << "\n\t\t\t\t\t\t\t0. ANY OTHER TO EXIT";
    int n;
    cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
    cout << "\n\t\t\t\t\t\t\tINPUT: ";
    cin >> n;
    return n;
}
int teacherPage()
{
    titleBar();
    cout << "\n\t\t\t\t\t\t\t1. GET DETAILS";
    cout << "\n\t\t\t\t\t\t\t2. REPORT POSITIVE";
    cout << "\n\t\t\t\t\t\t\t3. COVID-19 SEARCH";
    cout << "\n\t\t\t\t\t\t\t4. NEWS AND UPDATES";
    cout << "\n\t\t\t\t\t\t\t5. BACK TO MAIN PAGE";
    cout << "\n\t\t\t\t\t\t\t0. ANY OTHER TO EXIT";
    int n;
    cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
    cout << "\n\t\t\t\t\t\t\tINPUT: ";
    cin >> n;
    return n;
}

int adminPage()
{
    titleBar();
    cout << "\n\t\t\t\t\t\t\t1. GET DETAILS";
    cout << "\n\t\t\t\t\t\t\t2. CHANGE STUDENT INSTRUCTIONS";
    cout << "\n\t\t\t\t\t\t\t3. CHANGE TEACHERS INSTRUCTIONS";
    cout << "\n\t\t\t\t\t\t\t4. BACK TO MAIN PAGE";
    cout << "\n\t\t\t\t\t\t\t0. TO EXIT";
    int n;
    cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
    cout << "\n\t\t\t\t\t\t\tINPUT: ";
    cin >> n;
    return n;
}

void terminated()
{
    cout << "\n\t\t\t\t\t\t      -----------------------------------------";
    cout << "\n\t\t\t\t\t\t\t\t  PROGRAM TERMINATED";
    cout << "\n\t\t\t\t\t\t      -----------------------------------------";
    exit(0);
}

//STUDENTS
//Batch no. 65
Date dt1(15, 9, 2020);
Student s61("992061", "Siddhart Malhotra", "Noida-113", "993873723", 65, dt1);
Student s62("992062", "Rhthm Shandlya", "Bihar", "9920398765", 65, dt1);
Student s63("992063", "Anshuman Tyagi", "Chennai", "9914256543", 65, dt1);
Student s64("992064", "Ananya Garg", "Noida-62", "9856729512", 65, dt1);
Student s65("992065", "Sahil Kapoor", "Agra", "8976854321", 65, dt1);
Student s66("992066", "Raghav Vij", "Rohtak", "8979806875", 65, dt1);
//Batch no. 66
Date dt2(15, 10, 2020);
Student s67("992067", "Raj Gupta", "Noida-69", "6789549403", 66, dt2);
Student s68("992068", "Utsav Jain", "rajnagar", "993873723", 66, dt2);
Student s69("992069", "Virat Kohli", "Mumbai", "9938456374", 66, dt2);
Student s70("992070", "Amvi Sinha", "Lucknow", "993873723", 66, dt2);
Student s71("992071", "Apoorva Jain", "Noida-69", "995674723", 66, dt2);
//Batch no. 67
Date dt3(30, 10, 2020);
Student s72("992072", "Anu kumar", "Noida", "945633723", 67, dt3);
Student s73("992073", "Ayushman khurana", "Jammu", "993873723", 67, dt3);
Student s74("992074", "Ramu Kaka", "Rajasthan", "993867853", 67, dt3);
Student s75("992075", "Rhthm Sharma", "muzzafarnagar", "993873723", 67, dt3);
Student s76("992076", "Muskan Sharma", "Narula", "993908723", 67, dt3);

vector<Student> students = {s61, s62, s63, s64, s65, s66, s67, s68, s69, s70, s71, s72, s73, s74, s75, s76};
//Teachers
Teacher T1("101", "SDF", "Mukesh saraswat", "Agra", "9910020304", "TRUE", {65, 66});
Teacher T2("102", "English", "Swati Pandey", "Agra", "9910020304", "TRUE", {67, 66});
Teacher T3("103", "Physics", "Muskan saraswat", "Delhi", "9910049504", "TRUE", {65, 66});
Teacher T4("104", "SDF", "Raj Mehta", "Allahbad", "9910450304", "TRUE", {65, 67});
Teacher T5("105", "Chemistry", "Mukesh Verma", "Kolkata", "9910024504", "TRUE", {67, 66});
vector<Teacher> teachers = {T1, T2, T3, T4, T5};

/*ADMIN*/
Admin A1("1101", "Rhythm Shandlya", "733852013");
Admin A2("1102", "Raghav Vij", "8789436390");
Admin A3("1103", "Ananya Garg", "9939342567");
vector<Admin> admin{A1, A2, A3};

string snews = "\n\t\t\t\t\t\t\t#Examination will be on mettl platform",
       tnews = "\n\t\t\t\t\t\t\t#Examination will be on mettl platform";
void news(char ch)
{
    int stud_vacc = 5;
    int teach_vacc = 5;
    cout << "\n\t\t\t\t\t\t\tTotal COVID cases:" << covidcase;
    cout << "\n\t\t\t\t\t\t\tNo. of vaccinated students on campus" << stud_vacc;
    cout << "\n\t\t\t\t\t\t\tNo. of vaccinated teachers on campus" << teach_vacc;
    cout << "\n\t\t\t\t\t\t\t#Masks and sanitizer compulsory on campus grounds,otherwise fine of Rs.2000/- will be charged." << endl;
    if (ch == 't')
        cout << tnews << endl;
    else
        cout << snews;
}

bool searchCases(string id)
{
    ifstream in("POSITIVE.txt", ios::in);
    if (!in)
    {
        cout << "\nUnable to open a required file!\n";
        return "-1";
    }
    while (!in.eof())
    {
        char data[30] = "";
        in.getline(data, 30, '\n');
        if (strcmp(data, id.c_str()) == 0)
            return true;
    }
    return false;
}

void reportPositive(string id)
{
    ofstream op("POSITIVE.txt", ios::app);
    op << id << "\n";
    op.close();
}

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
                int k;
                do
                {
                STUDENT_0:
                    k = studentPage();
                    if (k == 1)
                    {
                        for (Student s : students)
                        {
                            if (s.eRoll == str)
                            {
                                s.print();
                                int m;
                                cout << "\n\t\t\t\t\t\t\t0. BACK ";
                                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                                cout << "\n\t\t\t\t\t\t\tINPUT: ";
                                cin >> m;
                                if (m == 0)
                                {
                                    goto STUDENT_0;
                                }
                                else
                                {
                                    goto MAIN;
                                }
                            }
                        }
                    }
                    else if (k == 2)
                    {
                        reportPositive(str);
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                        cout << "\n\t\t\t\t\t\t\t\t  DATA REGISTERED";
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                        sleep(1);
                    }
                    else if (k == 3)
                    {
                        cout << "\n\t\t\t\t\t\t\tEnter user ID to search: ";
                        string std;
                        cin >> std;
                        if (searchCases(std))
                        {
                            cout << "\n\t\t\t\t\t\t\tYES, the user associated with this\n\t\t\t\t\t\t\tID is COVID-19 positive!";
                        }
                        else
                        {
                            cout << "\n\t\t\t\t\t\t\tThe user associated with this\n\t\t\t\t\t\t\t ID is safe!";
                        }
                        int m;
                        cout << "\n\t\t\t\t\t\t\t0. BACK ";
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                        cout << "\n\t\t\t\t\t\t\tINPUT: ";
                        cin >> m;
                        if (m == 0)
                        {
                            goto STUDENT_0;
                        }
                        else
                        {
                            goto MAIN;
                        }
                    }
                    else if (k == 4)
                    {
                        news('s');
                        int m;
                        cout << "\n\t\t\t\t\t\t\t0. BACK ";
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                        cout << "\n\t\t\t\t\t\t\tINPUT: ";
                        cin >> m;
                        if (m == 0)
                        {
                            goto STUDENT_0;
                        }
                        else
                        {
                            goto MAIN;
                        }
                    }
                    else if (k == 5)
                    {
                        goto MAIN;
                    }
                    else if (k == 0)
                    {
                        terminated();
                    }
                } while (true);
            }
            else
            {
            STUDENT_2:
                cout << "\n\t\t\t\t\t\t\t\t0. BACK TO MAIN SCREEN";
                cout << "\n\t\t\t\t\t\t\t\t1. RETRY LOGIN";
                int m;
                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\tINPUT: ";
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
            TEACHER_0:
                int k;
                do
                {
                    k = teacherPage();
                    if (k == 1)
                    {
                        for (Teacher t : teachers)
                        {
                            if (t.teacherId == str)
                            {
                                t.print();
                                int m;
                                cout << "\n\t\t\t\t\t\t\t0)BACK ";
                                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                                cout << "\n\t\t\t\t\t\t\tINPUT: ";
                                cin >> m;
                                if (m == 0)
                                {
                                    goto TEACHER_0;
                                }
                                else
                                {
                                    goto MAIN;
                                }
                            }
                        }
                    }
                    else if (k == 2)
                    {
                        reportPositive(str);
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                        cout << "\n\t\t\t\t\t\t\t\t  DATA REGISTERED";
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------";
                        sleep(1);
                    }
                    else if (k == 3)
                    {
                        cout << "\n\t\t\t\t\t\t\tEnter user ID to search: ";
                        string std;
                        cin >> std;
                        if (searchCases(std))
                        {
                            cout << "\n\t\t\t\t\t\t\tYES, the user associated with this ID is COVID-19 positive!";
                        }
                        else
                        {
                            cout << "\n\t\t\t\t\t\t\tThe user associated with this ID is safe!";
                        }
                        int m;
                        cout << "\n\t\t\t\t\t\t\t0. BACK ";
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                        cout << "\n\t\t\t\t\t\t\tINPUT: ";
                        cin >> m;
                        if (m == 0)
                        {
                            goto TEACHER_0;
                        }
                        else
                        {
                            goto MAIN;
                        }
                    }
                    else if (k == 4)
                    {
                        news('t');
                        int m;
                        cout << "\n\t\t\t\t\t\t\t0. BACK ";
                        cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                        cout << "\n\t\t\t\t\t\t\tINPUT: ";
                        cin >> m;
                        if (m == 0)
                        {
                            goto TEACHER_0;
                        }
                        else
                        {
                            goto MAIN;
                        }
                    }
                    else if (k == 5)
                    {
                        goto MAIN;
                    }
                    else if (k == 0)
                    {
                        terminated();
                        return 0;
                    }
                } while (true);
            }
            else
            {
            TEACHER_2:
                cout << "\n\t\t\t\t\t\t\t\t0. BACK TO MAIN SCREEN";
                cout << "\n\t\t\t\t\t\t\t\t1. RETRY LOGIN";
                int m;
                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\tINPUT: ";
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
            auto it = find(admin.begin(), admin.end(), str);
            if (str != "-1")
            {
                int k;
                do
                {
                    k = adminPage();
                    if (k == 1)
                    {
                        it->print();
                        char j;
                        cout << "\n\t\t\t\t\t\t\t  PRESS ANYTHING WITH ENTER GET BACK";
                        cout << "\n\t\t\t\t\t\t\tINPUT: ";
                        cin >> j;
                    }
                    else if (k == 2)
                    {
                        system("CLS");
                        cout << "ENTER DETAILS: " << endl;
                        fflush(stdin);
                        getline(cin >> ws, snews);
                    }
                    else if (k == 3)
                    {
                        system("CLS");
                        cout << "ENTER DETAILS: " << endl;
                        fflush(stdin);
                        getline(cin >> ws, tnews);
                    }
                    else if (k == 4)
                    {
                        goto MAIN;
                    }
                    else if (k == 0)
                    {
                        terminated();
                        return 0;
                    }
                } while (true);
            }
            else
            {
            ADMIN_2:
                cout << "\n\t\t\t\t\t\t\t\t0. BACK TO MAIN SCREEN";
                cout << "\n\t\t\t\t\t\t\t\t1. RETRY LOGIN";
                int m;
                cout << "\n\t\t\t\t\t\t      -----------------------------------------\n";
                cout << "\n\t\t\t\t\t\t\tINPUT: ";
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
        if (n == 0)
        {
            terminated();
        }
    } while (n == 1 || n == 2 || n == 3);
    return 0;
}