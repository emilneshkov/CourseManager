#include "Student.h"

Student::Student(int id, const MyString& firstName, const MyString& lastName, const MyString& email, const MyString& password, const MyVector<Message>& inbox) : User(id, firstName, lastName, email, password, inbox, Role::Student)
{
}

Student::Student(int id, const MyString& firstName, const MyString& lastName, const MyString& password) :User(id, firstName, lastName, MyString(), password, MyVector<Message>(), Role::Student)
{
}

User* Student::clone() const
{
    return new Student(*this);
}
