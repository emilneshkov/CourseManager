#pragma once
#include "Command.h"

class AddTeacherCommand :public Command
{
public:
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

