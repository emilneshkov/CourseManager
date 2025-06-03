#include "MessageAllCommand.h"
#include "Admin.h"

void MessageAllCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() < 2) {
        std::cout << "Usage: message_all <content>\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser || currentUser->getRole() != User::Role::Admin) {
        std::cout << "Error: Only administrator can send global messages.\n";
        return;
    }
    Admin* admin = static_cast<Admin*>(currentUser);


    MyString content;
    for (size_t i = 1; i < arguments.getSize(); ++i) {
        content += arguments[i];

        if (i + 1 < arguments.getSize()) {
            content.pushBack(' ');
        }
    }

    try {
        admin->messageAll(content, courseApp.getUserRepo());
        std::cout << "Message sent to all users.\n";
    }
    catch (const std::exception& e) {
        std::cout << "Failed to send message: " << e.what() << "\n";
    }
}
