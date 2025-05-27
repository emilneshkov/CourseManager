#pragma once
#include "User.h"
#include "UserRepository.h"

class Admin : public User
{
public:
	Admin(int id,
		const MyString& firstName, 
		const MyString& lastName, 
		const MyString& email,
		const MyString& password,
		const MyVector<Message>& inbox);

	User* clone() const override;

	int addTeacher(const MyString& firstName, const MyString& lastName, const MyString& defaultPass, UserRepository& userRepo);

	int addStudent(const MyString& firstName, const MyString& lastName, const MyString& defaultPass, UserRepository& userRepo);

	void messageAll(const MyString& content, UserRepository& userRepo);

	const MyVector<Message>& viewInboxOf(int userId, UserRepository& userRepo) const;
};

