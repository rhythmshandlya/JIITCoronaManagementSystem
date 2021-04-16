#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Student;

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
    void print()
    {
        cout << "\nSTUDENT DETAILS";
        cout << "\nEnrolment Number: " << eRoll;
        cout << "\nName: " << name;
        cout << "\nAddress: " << address;
        cout << "\nContact Number" << phoneNumber;
    }
    Student(string er = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL") : Person{n, add, pn}, eRoll{er} {}
};
class Teacher : public Person
{
public:
    string teacherId;
    string subject;
    bool vaccined;
    void print()
    {
        cout << "\nTEACHER DETAILS";
        cout << "\nFaculty ID: " << teacherId;
        cout << "\nSubject: " << subject;
        cout << "\nName: " << name;
        cout << "\nAddress: " << address;
        cout << "\nContact Number" << phoneNumber;
        if (vaccined)
            cout << "\nCOVID-19 immune";
        else
            cout << "\nNOT VACCINATED for COVID-19 yet";
    }
    Teacher(string tId = "NULL", string sub = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL", bool bl = false) : Person{n, add, pn}, teacherId{tId}, vaccined{bl}, subject{sub} {}
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
        Student *s = new Student(er, n, add, pn);
        student.push_back(s);
        return student.size();
    }
    int addStudent(Student *s)
    {
        student.push_back(s);
        return student.size();
    }
    int addTeacher(string tId = "NULL", string sub = "NULL", string n = "NULL", string add = "NULL", string pn = "NULL", bool bl = false)
    {
        Teacher *t = new Teacher(tId, sub, n, add, pn);
        teacher.push_back(t);
        return teacher.size();
    }
    int addTeacher(Teacher *s)
    {
        teacher.push_back(s);
        return teacher.size();
    }
};

int main()
{

    /*
        Person is a interface and print() is the purely virtual function overridden in Student and Teacher classes
        We cannot instanciate the person class.DO NOT MAKE REAL OBJECTS OF THE PERSON CLASS.
    */
    Person *p1, *p2;

    /*
        How to use Student's constructor: 
        Student(enrolmentNo,name,address,contactNo);
        Sturdent();
    */
    Student *s1 = new Student("9920102062", "Rhythm Shandlya", "Bhagalpur, Bihar", "7338520113");

    /*
        How to use Teacher's constructor:
        Teacher(teacherId,subject,name,address,contactNo,beenVaccinated);
        Teacher();
    */
    Teacher *t1 = new Teacher("1102", "CSE", "Sumit Arora", "Noida-118", "1234567890", true);

    p1 = s1;
    p2 = t1;
    p1->print();
    cout << endl;
    p2->print();
    cout << endl;

    /*
        How to use Batch's constructor:
        Batch(batchId);
        Batch(batchId,vectorOfStudentsPointers, vectorOfTeacherPointers);
    */
    Batch F3(65);

    F3.addStudent(s1);
    F3.addStudent("9920102068", "Ananya Garg", "Delhi", "6283779213");
    F3.addTeacher(t1);
    F3.addTeacher("1104", "Physics", "Vijay Kumar", "Noida-62", "2345634390", false);

    //Accessing Student deatils of batch F3
    F3.student[0]->print(); 
    cout<<endl;
    F3.student[1]->print();
    cout<<endl;
    //Accessing Teachers detail of batch F3
    F3.teacher[0]->print();
    cout<<endl;
    F3.teacher[1]->print();
    cout<<endl;

    return 0;
}