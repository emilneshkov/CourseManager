#include "ClearMailboxCommand.h"

void ClearMailboxCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 1) {
        std::cout << "Usage: clear_mailbox\n";
        return;
    }

    User* currentUser = courseApp.getCurrentUser();
    if (!currentUser) {
        std::cout << "Error: no user logged in.\n";
        return;
    }

    currentUser->clearInbox();
    std::cout << "Mailbox cleared.\n";
}
