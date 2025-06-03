#include "MessageCommand.h"

void MessageCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() < 3) {
        std::cout << "Usage: message <recipientId> <content>\n";
        return;
    }

    User* sender = courseApp.getCurrentUser();
    if (!sender) {
        std::cout << "Error: you must be logged in to send a message.\n";
        return;
    }

    int recipientId = arguments[1].parseToInt();

    MyString content;
    for (size_t i = 2; i < arguments.getSize(); ++i) {
        content += arguments[i];
        if (i + 1 < arguments.getSize())
            content.pushBack(' ');
    }

    try {
        User& recipient = courseApp.getUserRepo().findById(recipientId);

        Message msg(sender->getId(), content, std::time(nullptr));
        recipient.receiveMessage(msg);

        std::cout << "Message sent to user " << recipientId << ".\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to send message: " << ex.what() << "\n";
    }
}
