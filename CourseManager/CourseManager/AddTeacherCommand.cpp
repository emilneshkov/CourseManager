#include "AddTeacherCommand.h"
#include "Admin.h"

void AddTeacherCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() != 4) {
		std::cout << "Usage: add_teacher <FirstName> <LastName> <DefaultPass>\n";
		return;
	}

	User* currentUser = courseApp.getCurrentUser();
	if (!currentUser || currentUser->getRole() != User::Role::Admin) {
		std::cout << "Error: Only administrator can add teachers.\n";
		return;
	}
	Admin* admin = static_cast<Admin*>(currentUser);

	const MyString& firstName = arguments[1];
	const MyString& lastName = arguments[2];
	const MyString& defaultPass = arguments[3];

	try {
		int newId = admin->addTeacher(firstName, lastName, defaultPass,
			courseApp.getUserRepo());

		std::cout << "Added teacher "<< firstName.getString() << " " << lastName.getString()<< " with ID " << newId << "!\n";
	}
	catch(const std::exception& ex){
		std::cout << "Failed to add teacher: " << ex.what() << "\n";
	}
}
