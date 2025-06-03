#include "Course.h"
#include <fstream>
#include "StringHelper.h"

Course::Course()
{
	this->id = -1;
	this->name = MyString();
	this->teacherId = -1;
	this->enrollmentPassword = MyString();
	this->studentIds = MyVector<int>();
	this->assignments = MyVector<Assignment>();
}

Course::Course(int id, const MyString& name, int teacherId)
{
	this->id = id;
	this->name = name;
	this->teacherId = teacherId;
	this->enrollmentPassword = MyString();
	this->studentIds = MyVector<int>();
	this->assignments = MyVector<Assignment>();
}

int Course::getId() const
{
	return id;
}

const MyString& Course::getName() const
{
	return name;
}

int Course::getTeacherId() const
{
	return teacherId;
}

const MyString& Course::getEnrollmentPassword() const
{
	return enrollmentPassword;
}

const MyVector<int>& Course::getStudentIds() const
{
	return studentIds;
}

bool Course::isStudentEnrolled(int studentId) const
{
	if (studentIds.contains(studentId)) {
		return true;
	}
	return false;
}

bool Course::canEnroll(const MyString& password) const
{
	return !enrollmentPassword.empty() && enrollmentPassword == password;
}

void Course::enroll(int studentId)
{
	studentIds.pushBack(studentId);
}

void Course::setEnrollmentPassword(const MyString& newPassword)
{
	enrollmentPassword = newPassword;
}

int Course::getNewAssigmentId() const
{
	return assignments.getSize() + 1;
}

void Course::addAssignment(const Assignment& newAsssignment)
{
	assignments.pushBack(newAsssignment);
}

const Assignment& Course::getAssigmentById(int assignmentId) const
{
	for (size_t i = 0; i < assignments.getSize(); i++)
	{
		if (assignments[i].getAssignmentId() == assignmentId) {
			return assignments[i];
		}
	}
	throw std::logic_error("Assignment not found");
}

Assignment& Course::getAssigmentById(int assignmentId)
{
	for (size_t i = 0; i < assignments.getSize(); i++)
	{
		if (assignments[i].getAssignmentId() == assignmentId) {
			return assignments[i];
		}
	}
	throw std::logic_error("Assignment not found");
}

const Assignment& Course::getAssigmentByTittle(const MyString& assignmentTitle) const
{
	for (size_t i = 0; i < assignments.getSize(); i++)
	{
		if (assignments[i].getTitle() == assignmentTitle) {
			return assignments[i];
		}
	}
	throw std::logic_error("Assignment not found");
}

Assignment& Course::getAssigmentByTittle(const MyString& assignmentTitle)
{
	for (size_t i = 0; i < assignments.getSize(); i++)
	{
		if (assignments[i].getTitle() == assignmentTitle) {
			return assignments[i];
		}
	}
	throw std::logic_error("Assignment not found");
}

const MyVector<Assignment>& Course::getAssignments() const
{
	return assignments;
}

void Course::saveToBinary(std::ofstream& ofs) const 
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	writeString(ofs, name);
	ofs.write(reinterpret_cast<const char*>(&teacherId), sizeof(teacherId));
	writeString(ofs, enrollmentPassword);


	size_t ns = studentIds.getSize();
	ofs.write(reinterpret_cast<const char*>(&ns), sizeof(ns));

	for (size_t i = 0; i < ns; ++i) {
		int sid = studentIds[i];
		ofs.write(reinterpret_cast<const char*>(&sid), sizeof(sid));
	}

	size_t na = assignments.getSize();
	ofs.write(reinterpret_cast<const char*>(&na), sizeof(na));

	for (size_t i = 0; i < na; ++i) {
		assignments[i].saveToBinary(ofs);
	}
}

void Course::loadFromBinary(std::ifstream& ifs) 
{
	ifs.read(reinterpret_cast<char*>(&this->id), sizeof(this->id));
	readString(ifs, this->name);
	ifs.read(reinterpret_cast<char*>(&this->teacherId), sizeof(this->teacherId));
	readString(ifs, this->enrollmentPassword);

	size_t ns;
	ifs.read(reinterpret_cast<char*>(&ns), sizeof(ns));
	studentIds.clear();

	for (size_t i = 0; i < ns; ++i) {
		int sid;
		ifs.read(reinterpret_cast<char*>(&sid), sizeof(sid));
		studentIds.pushBack(sid);
	}

	size_t na;
	ifs.read(reinterpret_cast<char*>(&na), sizeof(na));

	assignments.clear();
	assignments.reserve(na);

	for (size_t i = 0; i < na; ++i) {
		Assignment a;
		a.loadFromBinary(ifs);
		assignments.pushBack(a);
	}
}