#pragma once
#include "MyString.h";
#include "MyVector.hpp";
#include "Assignment.h"
#include <fstream>

class Course
{
	int id;
	MyString name;
	int teacherId;
	MyString enrollmentPassword;
	MyVector<int> studentIds;
	MyVector<Assignment> assignments;

public:
	Course();
	Course(int id, const MyString& name, int teacherId);

	int getId() const;
	const MyString& getName() const;
	int getTeacherId() const;
	const MyString& getEnrollmentPassword() const;
	const MyVector<int>& getStudentIds()const;
	MyVector<int>& getStudentIds();

	bool isStudentEnrolled(int studentId)const;
	bool canEnroll(const MyString& password) const;
	void enroll(int studentId);
	void setEnrollmentPassword(const MyString& newPassword);


	int getNewAssigmentId()const;
	void addAssignment(const Assignment& newAssigment);

	const Assignment& getAssigmentById(int assignmentId) const;
	Assignment& getAssigmentById(int assignmentId);

	const Assignment& getAssigmentByTittle(const MyString& assignmentTitle) const;
	Assignment& getAssigmentByTittle(const MyString& assignmentTitle);

	const MyVector<Assignment>& getAssignments() const;

	void saveToBinary(std::ofstream& ofs) const;
	void loadFromBinary(std::ifstream& ifs);
};

