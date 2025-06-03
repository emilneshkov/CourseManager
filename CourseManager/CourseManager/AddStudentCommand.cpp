#include "AddStudentCommand.h"
#include "Admin.h"

void AddStudentCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 4) {
        std::cout << "Usage: add_student <firstName> <lastName> <defaultPassword>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Admin) {
        std::cout << "Error: only the administrator may add students.\n";
        return;
    }
    Admin& admin = static_cast<Admin&>(*currentUser);

    const MyString& firstName = arguments[1];
    const MyString& lastName = arguments[2];
    const MyString& defaultPass = arguments[3];

    try {
        int newId = admin.addStudent(firstName, lastName, defaultPass, courseApp.getUserRepo());

        std::cout << "Added student "<< firstName.getString() << " "<< lastName.getString()<< " with ID " << newId << "!\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to add student: " << ex.what() << "\n";
    }
}
