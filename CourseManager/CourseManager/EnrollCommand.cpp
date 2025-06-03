#include "EnrollCommand.h"
#include "Student.h"

void EnrollCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 3) {
        std::cout << "Usage: enroll <courseName> <password>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Student) {
        std::cout << "Error: only a student may enroll in a course.\n";
        return;
    }
    Student& student = static_cast<Student&>(*currentUser);

    const MyString& courseName = arguments[1];
    const MyString& password = arguments[2];

    try {
        student.enrollInCourse(courseName, password, courseApp.getCourseRepo());
        std::cout << "Successfully enrolled in "<< courseName.getString() << "!\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to enroll: " << ex.what() << "\n";
    }
}
