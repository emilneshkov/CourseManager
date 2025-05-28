#include "ClearMailboxCommand.h"

void ClearMailboxCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
    if (arguments.getSize() != 1) {
        std::cout << "Usage: clear_mailbox\n";
        return;
    }

    User* user = courseApp.getCurrentUser();
    if (!user) {
        std::cout << "Error: no user logged in.\n";
        return;
    }

    user->clearInbox();
    std::cout << "Mailbox cleared.\n";
}
