#include "CourseManagerApp.h"
#include "CommandFactory.h"

namespace CONSTANTS {
	MyString userFile = "users.txt";
	MyString coursesFile = "courses.txt";
}

void CourseManagerApp::loadData()
{
	userRepo.load(CONSTANTS::userFile);
	//courseRepo.load(CONSTANTS::coursesFile);
}

void CourseManagerApp::saveData()
{
	userRepo.save(CONSTANTS::userFile);
	//courseRepo.save(CONSTANTS::coursesFile);
}

void CourseManagerApp::commandLoop()
{
	while (running) {
		std::cout << "> ";

		MyString line;
		char ch;

		while (std::cin.get(ch) && ch != '\n') {
			line.pushBack(ch);
		}

		if (!std::cin) break;
		if (line.empty()) continue;
		handleCommand(line);
	}
}
MyVector<MyString> CourseManagerApp::split(const MyString& line) const
{
	MyVector<MyString> tokens;
	MyString current;

	for (size_t i = 0; i < line.getSize(); ++i) {
		char c = line[i];

		if (c == ' ') {
			if (!current.empty()) {
				tokens.pushBack(current);
				current.clear();
			}
		}
		else {
			current.pushBack(c);
		}
	}
	if (!current.empty()) {
		tokens.pushBack(current);
	}

	return tokens;
}

void CourseManagerApp::handleCommand(const MyString& line)
{
	MyVector<MyString> arguments = split(line);

	if (arguments.empty()) {
		return;
	}

	Command* command = CommandFactory::create(arguments[0]);

	if (!command) {
		std::cout << "Unknown command: " << arguments[0] << std::endl;
		return;
	}

	command->execute(arguments, *this);
	delete command;
}

UserRepository& CourseManagerApp::getUserRepo()
{
	return userRepo;
}

User* CourseManagerApp::getCurrentUser() const
{
	return currentUser;
}

void CourseManagerApp::setCurrentUser(User* user)
{
	currentUser = user;
}

bool CourseManagerApp::isRunning() const
{
	return running;
}

void CourseManagerApp::stop()
{
	running = false;
}

CourseManagerApp::CourseManagerApp()
{
	loadData();
}

void CourseManagerApp::run()
{
	commandLoop();
}