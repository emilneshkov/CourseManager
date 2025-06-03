#include "AddAssignmentCommand.h"
#include "Teacher.h"

void AddAssignmentCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 3) {
        std::cout << "Usage: assign_homework <courseName> <assignmentTitle>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Teacher) {
        std::cout << "Error: only a teacher may assign homework.\n";
        return;
    }
    Teacher& teacher = static_cast<Teacher&>(*currentUser);

    const MyString& courseName = arguments[1];
    const MyString& assignmentTitle = arguments[2];

    try {
        int assignmentId = teacher.addAssignment(
            courseName,
            assignmentTitle,
            courseApp.getCourseRepo()
        );

        std::cout << "Successfully created assignment \""<< assignmentTitle.getString()<< "\" (ID " << assignmentId << ") in course \""<< courseName.getString() << "\"\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to assign homework: " << ex.what() << "\n";
    }
}
