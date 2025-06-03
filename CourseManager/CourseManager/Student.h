#pragma once
#include "User.h"
#include "CourseRepository.h"
#include "UserRepository.h"

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
		const MyString& password);

	User* clone() const override;

	void enrollInCourse(const MyString& courseName, const MyString& coursePassword, CourseRepository& courseRepo);

	void submitAssignment(const MyString& courseName, const MyString& assignmentTitle, const MyString& content, CourseRepository& courseRepo) const;

	MyVector<Grade> viewMyGrades(const CourseRepository& courseRepo) const;

	void sendMessage(int toUserId, const MyString& content, UserRepository& userRepo);
};

