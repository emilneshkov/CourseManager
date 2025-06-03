#include "MessageStudentsCommand.h"
#include "Teacher.h"

void MessageStudentsCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() < 3) {
        std::cout << "Usage: message_students <courseName> <message>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Teacher) {
        std::cout << "Error: only a teacher may message course students.\n";
        return;
    }
    Teacher& teacher = static_cast<Teacher&>(*currentUser);

    const MyString& courseName = arguments[1];

    MyString content;
    for (size_t i = 2; i < arguments.getSize(); ++i) {
        content += arguments[i];
        if (i + 1 < arguments.getSize()) {
            content.pushBack(' ');
        }
    }

    try {
        teacher.messageCourseStudents(courseName,content,courseApp.getCourseRepo(),courseApp.getUserRepo());

        std::cout << "Message sent to students of \""<< courseName.getString() << "\"\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to send message: " << ex.what() << "\n";
    }
}
