#include "LoginCommand.h"

void LoginCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() != 3) {
		std::cout << "Usage: login <id> <password>\n";
		return;
	}

	if(courseApp.getCurrentUser()){
		std::cout << "A user is already logged!\n";
		return;
	}

	int id = arguments[1].parseToInt();
	const MyString& pwd = arguments[2];


	User& user = courseApp.getUserRepo().findById(id);

	if (!user.checkPassword(pwd)) {
		std::cout << "Invalid password.\n";
		return;
	}
	courseApp.setCurrentUser(&user);
	std::cout << "Login successful!\n";
}
