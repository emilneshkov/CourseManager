#include "MailboxCommand.h"
#pragma warning(disable : 4996)
#include <iomanip>

void MailboxCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() != 1) {
		std::cout << "Usage: mailbox\n";
		return;
	}

	User* currentUser = courseApp.getCurrentUser();
	if (!currentUser) {
		std::cout << "Error: no user logged in.\n";
		return;
	}

	const MyVector<Message>& inbox = currentUser->getInbox();
	if (inbox.getSize() == 0) {
		std::cout << "No messages to show!\n";
		return;
	}

	for (size_t i = 0; i < inbox.getSize(); ++i) {
		const Message& message = inbox[i];

		time_t timeStamp = message.getTimestamp();

		std::tm* localTime = std::localtime(&timeStamp);

		std::cout << std::put_time(localTime, "%H:%M %d.%m.%Y") << ", sent by ";

		User& sender = courseApp.getUserRepo().findById(message.getSenderId());
		if (sender.getLastName().getSize() > 0) {
			std::cout << sender.getFirstName().getString() << " " << sender.getLastName().getString();
		}
		else {
			std::cout << "admin";
		}
		std::cout << ": " << message.getContent().getString() << "\n";
	}
}
