#include "MailboxCommand.h"
#pragma warning(disable : 4996)
#include <iomanip>

void MailboxCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 1) {
        std::cout << "Usage: mailbox\n";
        return;
    }

    User* user = courseApp.getCurrentUser();
    if (!user) {
        std::cout << "Error: no user logged in.\n";
        return;
    }

    const MyVector<Message>& inbox = user->getInbox();
    if (inbox.getSize() == 0) {
        std::cout << "No messages to show!\n";
        return;
    }


    for (size_t i = 0; i < inbox.getSize(); ++i) {
        const Message& message = inbox[i];

        time_t timeStamp = message.getTimestamp();

        std::tm* localTime = std::localtime(&timeStamp);

        std::cout
            <<std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << ", sent by ";

        try {
            User& sender = courseApp.getUserRepo().findById(message.getSenderId());
            std::cout << sender.getFirstName().getString()
                << " " << sender.getLastName().getString();
        }
        catch (...) {
            std::cout << "Unknown(" << message.getSenderId() << ")";
        }

        std::cout << ": "
            << message.getContent().getString()
            << "\n";
    }
}
