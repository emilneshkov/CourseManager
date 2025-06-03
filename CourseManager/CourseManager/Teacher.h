#pragma once
#include "User.h";
#include "Student.h"
#include "UserRepository.h"
#include "CourseRepository.h"

class Teacher :public User
{
public:
	Teacher(int id,
		const MyString& firstName,
		const MyString& lastName,
		const MyString& email,
		const MyString& password,
		const MyVector<Message>& inbox);

	Teacher(int id,
		const MyString& firstName,
		const MyString& lastName,
		const MyString& defaultPass);

	User* clone() const override;

	int createCourse(const MyString& courseName, CourseRepository& courseRepo);
	void setCourseEnrollmentPassword(int courseId, const MyString& newPassword, CourseRepository& courseRepo);
	int addAssignment(const MyString& courseName, const MyString& title, CourseRepository& courseRepo);
	void enrollStudentManually(int courseId, int studentId, CourseRepository& courseRepo);

	void gradeSubmission(int courseId, int assignmentId, int studentId, double score, const MyString& comment, CourseRepository& courseRepo);
	void viewSubmissions(const MyString& courseName, const MyString& assignmentTitle, const CourseRepository& courseRepo,const UserRepository& userRepo)const;

	void messageCourseStudents(const MyString& courseName, const MyString& content, CourseRepository& courseRepo, UserRepository& userRepo);
};