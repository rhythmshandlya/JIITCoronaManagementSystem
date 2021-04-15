#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

int main()
{
    /*
        Person is a interface and print() is the purely virtual function overridden in student and teacher classes
        We cannot instanciate the person class.DO NOT MAKE OBJECTS OF THE PERSON CLASS.
    */
    Person *p1, *p2;
    /*
        Order of arguments for the constructor of Student class
        Student(enrolmentNo,name,address,contactNo,beenVaccinated);
    */
    p1 = new Student("9920102062", "Rhythm Shandlya", "Bhagalpur, Bihar", "7338520113");
    /*
        Order of agruments for the constructor of Teacher class
        Teacher(teacherId,subject,name,address,contactNo,beenVaccinated);
    */
    p2 = new Teacher("1102", "CSE", "Sumit Arora", "Noida-118", "1234567890", true);

    p1->print();
    cout << endl;
    p2->print();
    cout << endl;
    system("pause");
    return 0;
}