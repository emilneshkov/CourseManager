#pragma once
#include "User.h"

class Admin : public User
{
public:
	Admin(int id,
		const MyString& firstName, 
		const MyString& lastName, 
		const MyString& email,
		const MyString& password,
		const MyVector<Message>& inbox);

	virtual ~Admin() = default;
};

