#include "LoginCommand.h"

void LoginCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() != 3) {
		std::cout << "Usage: login <id> <password>\n";
		return;
	}

	if (courseApp.getCurrentUser()) {
		std::cout << "A user is already logged!\n";
		return;
	}

	int id = arguments[1].parseToInt();
	const MyString& pwd = arguments[2];


	try {
		User& user = courseApp.getUserRepo().findById(id);
		if (!user.checkPassword(pwd)) {
			std::cout << "Invalid password.\n";
			return;
		}
		courseApp.setCurrentUser(&user);
		std::cout << "Login successful!\n";
		if (user.getLastName().getSize() > 0) {
			std::cout << user.getFirstName().getString() << " | " << user.getLastName().getString() << " | " << user.getId() << "\n";
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to login: " << ex.what() << "\n";
	}
}
