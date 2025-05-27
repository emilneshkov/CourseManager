#pragma once
#include "User.h"
class Student :public User
{
public:
	Student(int id,
		const MyString& firstName,
		const MyString& lastName,
		const MyString& email,
		const MyString& password,
		const MyVector<Message>& inbox);

	Student(int id,
		const MyString& firstName,
		const MyString& lastName,
		const MyString& email,
		const MyString& password);
};

