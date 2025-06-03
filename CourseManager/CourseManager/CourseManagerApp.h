#pragma once
#include "UserRepository.h"
#include "CourseRepository.h"

class CourseManagerApp
{
	UserRepository userRepo;
	CourseRepository courseRepo;

	User* currentUser = nullptr;
	bool running = true;

	void loadData();
	void saveData();
	void commandLoop();
	MyVector<MyString>split(const MyString& line) const;
	void handleCommand(const MyString& line);

public:
	CourseManagerApp();
	void run();

	UserRepository& getUserRepo();
	CourseRepository& getCourseRepo();

	User* getCurrentUser() const;
	void   setCurrentUser(User* user);

	bool   isRunning() const;
	void   stop();
};

