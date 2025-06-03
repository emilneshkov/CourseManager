#include "ChangePasswordCommand.h"

void ChangePasswordCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{

    if (arguments.getSize() != 3) {
        std::cout << "Usage: change_password <oldPassword> <newPassword>\n";
        return;
    }


    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser) {
        std::cout << "Error: no user logged in.\n";
        return;
    }

    const MyString& oldPass = arguments[1];
    const MyString& newPass = arguments[2];


    if (!currentUser->checkPassword(oldPass)) {
        std::cout << "Invalid current password.\n";
        return;
    }

    currentUser->changePassword(newPass);
    std::cout << "Password changed successfully!\n";
}
