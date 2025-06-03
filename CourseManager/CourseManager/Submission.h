#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Grade.h"

class Submission {
	int courseId;
	int assignmentId;
	int studentId;
	MyString content;
	MyVector<Grade> grade;

public:
	Submission();
	Submission(int courseId, int assigmentId, int studentId, const MyString& content);
	Submission(int courseId, int assigmentId, int studentId, const MyString& content, const MyVector<Grade>& grade);

	int getCourseId()const;
	int getAssigmentId() const;
	int getStudentId()const;
	const MyString& getContent()const;
	const Grade& getGrade()const;
	const MyVector<Grade>& getGradeVector()const;

	void gradeSubmission(const Grade& grade);

	void saveToBinary(std::ofstream& ofs) const;
	void loadFromBinary(std::ifstream& ifs);
};