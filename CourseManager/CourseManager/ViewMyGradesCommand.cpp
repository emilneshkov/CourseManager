#include "ViewMyGradesCommand.h"
#include "Student.h"

void ViewMyGradesCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() != 1) {
		std::cout << "Usage: grades\n";
		return;
	}

	User* currentUser = courseApp.getCurrentUser();
	if (!currentUser || currentUser->getRole() != User::Role::Student) {
		std::cout << "Error: only a student may view their grades.\n";
		return;
	}
	Student& student = static_cast<Student&>(*currentUser);

	const CourseRepository& courseRepo = courseApp.getCourseRepo();
	MyVector<Grade> grades = student.viewMyGrades(courseRepo);

	if (grades.getSize() == 0) {
		std::cout << "No grades available.\n";
		return;
	}

	for (size_t i = 0; i < grades.getSize(); ++i) {
		const Grade& grade = grades[i];

		std::cout << grade.getScore() << " | " << grade.getComment().getString() << "\n";
	}
}
