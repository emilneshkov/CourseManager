#include "CreateCourseCommand.h"
#include "Teacher.h"

void CreateCourseCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 3) {
        std::cout << "Usage: create_course <courseName> <enrollmentPassword>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Teacher) {
        std::cout << "Error: only a teacher may create courses.\n";
        return;
    }
    Teacher& teacher = static_cast<Teacher&>(*currentUser);

    const MyString& name = arguments[1];
    const MyString& password = arguments[2];

    try {
        int newId = teacher.createCourse(name, courseApp.getCourseRepo());

        teacher.setCourseEnrollmentPassword(newId, password, courseApp.getCourseRepo());
        std::cout << "Successfully created course \""<< name.getString() << "\" with ID " << newId << "\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to create course: " << ex.what() << "\n";
    }
}
