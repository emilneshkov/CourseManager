#include "SubmitAssignmentCommand.h"
#include "Student.h"

void SubmitAssignmentCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() < 4) {
        std::cout << "Usage: submit_assignment <courseName> <assignmentTitle> <content>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Student) {
        std::cout << "Error: only a student may submit assignments.\n";
        return;
    }
    Student& student = static_cast<Student&>(*currentUser);

    const MyString& courseName = arguments[1];
    const MyString& assignmentTitle = arguments[2];

    MyString content;
    for (size_t i = 3; i < arguments.getSize(); ++i) {
        content += arguments[i];

        if (i + 1 < arguments.getSize()) {
            content.pushBack(' ');
        }
    }

    try {
        student.submitAssignment(courseName, assignmentTitle, content, courseApp.getCourseRepo());

        std::cout << "Submitted assignment \""<< assignmentTitle.getString()<< "\" for course \""<< courseName.getString() << "\".\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to submit assignment: " << ex.what() << "\n";
    }
}
