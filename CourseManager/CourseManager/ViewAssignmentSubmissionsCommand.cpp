#pragma warning(disable : 4996)
#include <iomanip>
#include "ViewAssignmentSubmissionsCommand.h"
#include "Teacher.h"

void ViewAssignmentSubmissionsCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 3) {
        std::cout << "Usage: view_assignment_submissions <courseName> <assignmentTitle>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Teacher) {
        std::cout << "Error: only a teacher may view submissions.\n";
        return;
    }
    Teacher& teacher = static_cast<Teacher&>(*currentUser);

    const MyString& courseName = arguments[1];
    const MyString& assignmentTitle = arguments[2];

    try {
        teacher.viewSubmissions(courseName, assignmentTitle, courseApp.getCourseRepo(),courseApp.getUserRepo());
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to view submissions: " << ex.what() << "\n";
    }
}
