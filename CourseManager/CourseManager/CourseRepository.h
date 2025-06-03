#pragma once
#include "Course.h"

class CourseRepository
{
	MyVector<Course> courses;
public:
	const Course& findById(int courseId)const;
	Course& findById(int courseId);

	const Course& findByName(const MyString& courseName)const;
	Course& findByName(const MyString& courseName);

	void add(const Course& course);
	void removeById(int courseId);

	int getCoursesCount() const;
	int getNewCourseId()const;
	const MyVector<Course>& getAll() const;
	MyVector<Course>& getAll();

	void load(const MyString& filename);
	void save(const MyString& filename) const;
};

