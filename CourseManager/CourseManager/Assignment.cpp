#include "Assignment.h"
#include <fstream>
#include "StringHelper.h"

Assignment::Assignment()
{
	this->courseId = -1;
	this->assignmentId = -1;
	this->title = MyString();
	this->description = MyString();
	this->submissions = MyVector<Submission>();
}

Assignment::Assignment(int courseId, int assignmentId, const MyString& title)
{
	this->courseId = courseId;
	this->assignmentId = assignmentId;
	this->title = title;
	this->description = MyString();
	this->submissions = MyVector<Submission>();
}

Assignment::Assignment(int courseId, int assignmentId, const MyString& title, const MyString& description, const MyVector<Submission>& submissions)
{
	this->courseId = courseId;
	this->assignmentId = assignmentId;
	this->title = title;
	this->description = description;
	this->submissions = submissions;
}

int Assignment::getCourseId() const
{
	return courseId;
}

int Assignment::getAssignmentId() const
{
	return assignmentId;
}

const MyString& Assignment::getTitle() const
{
	return title;
}

const MyString& Assignment::getDescription() const
{
	return description;
}

void Assignment::addSubmission(const Submission& submission)
{
	submissions.pushBack(submission);
}

const MyVector<Submission>& Assignment::getSubmissions() const
{
	return submissions;
}

const Submission& Assignment::getSubbmissionByStudentId(int studentId) const
{
	for (size_t i = 0; i < submissions.getSize(); i++)
	{
		if (submissions[i].getStudentId() == studentId) {
			return submissions[i];
		}
	}
}

Submission& Assignment::getSubbmissionByStudentId(int studentId)
{
	for (size_t i = 0; i < submissions.getSize(); i++)
	{
		if (submissions[i].getStudentId() == studentId) {
			return submissions[i];
		}
	}
}

void Assignment::saveToBinary(std::ofstream& ofs) const 
{
	ofs.write(reinterpret_cast<const char*>(&courseId), sizeof(courseId));
	ofs.write(reinterpret_cast<const char*>(&assignmentId), sizeof(assignmentId));

	writeString(ofs, title);
	writeString(ofs, description);

	size_t ns = submissions.getSize();
	ofs.write(reinterpret_cast<const char*>(&ns), sizeof(ns));

	for (size_t i = 0; i < ns; i++)
	{
		submissions[i].saveToBinary(ofs);
	}
}

void Assignment::loadFromBinary(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&courseId), sizeof(courseId));
	ifs.read(reinterpret_cast<char*>(&assignmentId), sizeof(assignmentId));
	readString(ifs, title);
	readString(ifs, description);

	size_t ns;
	ifs.read(reinterpret_cast<char*>(&ns), sizeof(ns));
	submissions.clear();
	submissions.reserve(ns);

	for (size_t i = 0; i < ns; ++i) {
		Submission submission;

		submission.loadFromBinary(ifs);
			submissions.pushBack(submission);
	}
}