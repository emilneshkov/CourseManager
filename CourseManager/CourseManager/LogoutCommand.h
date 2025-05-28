#pragma once
#include "Command.h"

class LogoutCommand:public Command
{
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

