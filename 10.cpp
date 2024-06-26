#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
protected:
    string name;
    int age;

public:
    Person(const string &name, int age)
    {
        this->name = name;
        this->age = age;
    }

    virtual void display()
    {
        cout << "Name : " << name << "\n";
        cout << "Age : " << age << "\n";
    }
};

class Student : public Person
{
private:
    int rollno;
    static int nextStudentID;
    int studentID;

public:
    Student(const string &name, int age, const int &rollno) : Person(name, age), rollno(rollno)

    {
        studentID = nextStudentID++;
    }

    // Friend function to display Student
    friend ostream &displayStudent(ostream &os, const Student &student);

    int getStudentID()
    {
        return studentID;
    }
};

int Student::nextStudentID = 1;

ostream &displayStudent(ostream &os, const Student &student)
{
    os << "Student ID: " << student.studentID << "\n";
    os << "Name: " << student.name << "\n";
    os << "Age: " << student.age << "\n";
    os << "Roll no. : " << student.rollno << "\n";
    return os;
}

class Teacher : public Person
{
private:
    string subject;
    static int nextteacherID;
    int teacherID;

public:
    Teacher(const string &name, int age, const string &subject) : Person(name, age), subject(subject)

    {
        teacherID = nextteacherID++;
    }
    // Friend function to display Teacher
    friend ostream &displayTeacher(ostream &os, const Teacher &teacher);
    int getteacherID()
    {
        return teacherID;
    }
};
int Teacher::nextteacherID = 1;

ostream &displayTeacher(ostream &os, const Teacher &teacher)
{
    os << "Teacher ID: " << teacher.teacherID << "\n";
    os << "Name: " << teacher.name << "\n";
    os << "Age: " << teacher.age << "\n";
    os << "Subject: " << teacher.subject << "\n";
    return os;
}

class SchoolDatabase
{
private:
    vector<Person *> people;

public:
    void addPerson(Person *person)
    {
        people.push_back(person);
    }

    vector<Person *> &getPeople()
    {
        return people;
    }
};

int main()
{

    SchoolDatabase database;

    cout << "Enter no. of STUDENTS you want to add in school ";
    int s;
    cin >> s;

    cout << "Enter student information :" << endl
         << endl;
    string name;
    int age;
    int rollno;

    for (int i = 0; i < s; i++)
    {
        cout << "Enter student name : ";
        cin >> name;
        cout << "Enter age of student : ";
        cin >> age;
        int rollno;
        cin.ignore();
        cout << "Enter roll number of student : ";
        cin >> rollno;
        database.addPerson(new Student(name, age, rollno));
    }
    cout << endl;
    cout << "Enter no. of TEACHERS you want to add in school ";
    int t;
    cin >> t;

    cout << "Enter teacher information :" << endl;

    for (int i = 0; i < t; i++)
    {
        cout << "Enter teacher  name : ";
        cin >> name;
        cout << "Enter teacher age : ";
        cin >> age;
        string subject;
        cin.ignore();
        cout << "Enter subject teach by teacher : ";
        getline(cin, subject);
        database.addPerson(new Teacher(name, age, subject));
    }
    cout << endl;
    cout << "School Database:\n";
    for (const auto &person : database.getPeople())
    {
        if (dynamic_cast<Student *>(person) != nullptr)
        {
            displayStudent(cout, *dynamic_cast<Student *>(person));
        }
        else if (dynamic_cast<Teacher *>(person) != nullptr)
        {
            displayTeacher(cout, *dynamic_cast<Teacher *>(person));
        }
        cout << "\n";
    }

    return 0;
}
