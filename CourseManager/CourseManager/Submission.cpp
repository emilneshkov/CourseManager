#include "Submission.h"
#include <fstream>
#include "StringHelper.h"

Submission::Submission()
{
	this->courseId = -1;
	this->assignmentId = -1;
	this->studentId = -1;
	this->content = MyString();
	this->grade = MyVector<Grade>();
}

Submission::Submission(int courseId, int assigmentId, int studentId, const MyString& content)
{
	this->courseId = courseId;
	this->assignmentId = assigmentId;
	this->studentId = studentId;
	this->content = content;
	this->grade = MyVector<Grade>();
}

Submission::Submission(int courseId, int assigmentId, int studentId, const MyString& content, const MyVector<Grade>& grade)
{
	this->courseId = courseId;
	this->assignmentId = assigmentId;
	this->studentId = studentId;
	this->content = content;
	this->grade = grade;
}

int Submission::getCourseId() const
{
	return courseId;
}

int Submission::getAssigmentId() const
{
	return assignmentId;
}

int Submission::getStudentId() const
{
	return studentId;
}

const MyString& Submission::getContent() const
{
	return content;
}

const Grade& Submission::getGrade() const

{
	if (grade.empty()) {
		throw std::logic_error("Submission is not graded yet");
	}
	return grade[grade.getSize() - 1];
}

const MyVector<Grade>& Submission::getGradeVector() const
{
	return grade;
}

void Submission::gradeSubmission(const Grade& grade)
{
	if (this->grade.getSize() > 0) {
		throw std::logic_error("Submission is already graded");
	}
	this->grade.pushBack(grade);
}

void Submission::saveToBinary(std::ofstream& ofs) const 
{
	ofs.write(reinterpret_cast<const char*>(&courseId), sizeof(courseId));
	ofs.write(reinterpret_cast<const char*>(&assignmentId), sizeof(assignmentId));
	ofs.write(reinterpret_cast<const char*>(&studentId), sizeof(studentId));
	writeString(ofs, content);

	size_t ng = grade.getSize();
	ofs.write(reinterpret_cast<const char*>(&ng), sizeof(ng));
	for (size_t i = 0; i < ng; ++i) {
		grade[i].saveToBinary(ofs);
	}
}

void Submission::loadFromBinary(std::ifstream& ifs) 
{
	ifs.read(reinterpret_cast<char*>(&courseId), sizeof(courseId));
	ifs.read(reinterpret_cast<char*>(&assignmentId), sizeof(assignmentId));
	ifs.read(reinterpret_cast<char*>(&studentId), sizeof(studentId));
	readString(ifs, content);

	size_t ng;
	ifs.read(reinterpret_cast<char*>(&ng), sizeof(ng));
	grade.clear();
	grade.reserve(ng);

	for (size_t i = 0; i < ng; ++i) {
		Grade g;
		g.loadFromBinary(ifs);
		grade.pushBack(g);
	}
}