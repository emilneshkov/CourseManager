#include "CourseRepository.h"

const Course& CourseRepository::findById(int courseId)const
{
	for (size_t i = 0; i < courses.getSize(); ++i) {
		if (courses[i].getId() == courseId) {
			return courses[i];
		}
	}

	throw std::out_of_range("Course with ID not found");
}

Course& CourseRepository::findById(int courseId)
{
	for (size_t i = 0; i < courses.getSize(); ++i) {
		if (courses[i].getId() == courseId) {
			return courses[i];
		}
	}

	throw std::out_of_range("Course with ID not found");
}

const Course& CourseRepository::findByName(const MyString& courseName) const
{
	for (size_t i = 0; i < courses.getSize(); ++i) {
		if (courses[i].getName() == courseName) {
			return courses[i];
		}
	}

	throw std::out_of_range("Course not found or not your course");
}

Course& CourseRepository::findByName(const MyString& courseName)
{
	for (size_t i = 0; i < courses.getSize(); ++i) {
		if (courses[i].getName() == courseName) {
			return courses[i];
		}
	}

	throw std::out_of_range("Course not found or not your course");
}

void CourseRepository::add(const Course& course)
{
	courses.pushBack(course);
}

void CourseRepository::removeById(int courseId)
{
	for (size_t i = 0; i < courses.getSize(); ++i) {
		if (courses[i].getId() == courseId) {
			courses.erase(i);
			return;
		}
	}
	throw std::runtime_error("Course not found");
}

int CourseRepository::getCoursesCount() const
{
	return courses.getSize();
}

int CourseRepository::getNewCourseId() const
{
	return courses.getSize() + 1;
}

const MyVector<Course>& CourseRepository::getAll() const
{
	return courses;
}

MyVector<Course>& CourseRepository::getAll()
{
	return courses;
}

void CourseRepository::save(const MyString& filename) const
{
	std::ofstream ofs(filename.getString(), std::ios::binary);

	if (!ofs.is_open()) {
		throw std::runtime_error("Cannot open courses file for writing");
	}


	size_t n = courses.getSize();
	ofs.write(reinterpret_cast<const char*>(&n), sizeof(n));


	for (size_t i = 0; i < n; ++i) {
		courses[i].saveToBinary(ofs);
	}
}

void CourseRepository::load(const MyString& filename)
{
	courses.clear();

	std::ifstream ifs(filename.getString(), std::ios::binary);

	if (!ifs.is_open()) {
		std::ofstream ofs(filename.getString(),
			std::ios::binary);
		return;
	}

	size_t n = 0;
	ifs.read(reinterpret_cast<char*>(&n), sizeof(n));
	if (!ifs) {
		return;
	}

	for (size_t i = 0; i < n; ++i) {
		Course c;
		c.loadFromBinary(ifs);
		if (!ifs) {
			break;
		}

		courses.pushBack(c);
	}
}