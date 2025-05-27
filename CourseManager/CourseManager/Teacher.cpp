#include "Teacher.h"

Teacher::Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& email, const MyString& password, const MyVector<Message>& inbox) : User(id, firstName, lastName, email, password, inbox, Role::Teacher)
{
}
Teacher::Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& defaultPass) : User(id, firstName, lastName, MyString(), defaultPass, MyVector<Message>(), Role::Teacher)
{
}

User* Teacher::clone() const
{
	return new Teacher(*this);
}
