#include "LogoutCommand.h"

void LogoutCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() != 1) {
		std::cout << "Usage: logout \n";
		return;
	}

	courseApp.setCurrentUser(nullptr);
	std::cout << "Logout successful!\n";
}
