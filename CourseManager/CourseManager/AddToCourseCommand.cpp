#include "AddToCourseCommand.h"
#include "Teacher.h"

void AddToCourseCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 3) {
        std::cout << "Usage: add_to_course <courseName> <studentId>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Teacher) {
        std::cout << "Error: only a teacher may add students to a course.\n";
        return;
    }
    Teacher& teacher = static_cast<Teacher&>(*currentUser);

    const MyString& courseName = arguments[1];
    int studentId = arguments[2].parseToInt();

    try {
        User& candidate = courseApp.getUserRepo().findById(studentId);
        if (candidate.getRole() != User::Role::Student) {
            std::cout << "Error: user " << studentId << " is not a student.\n";
            return;
        }

        Course& course = courseApp.getCourseRepo().findByName(courseName);
        if (course.getTeacherId() != teacher.getId()) {
            std::cout << "Error: you are not the instructor for this course.\n";
            return;
        }

        teacher.enrollStudentManually(course.getId(), studentId, courseApp.getCourseRepo());

        std::cout << "Added student " << studentId << " to course \"" << courseName.getString() << "\"\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to add student: " << ex.what() << "\n";
    }
}
