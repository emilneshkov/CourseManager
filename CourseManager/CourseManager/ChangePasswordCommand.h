#pragma once
#include "Command.h"
#include "CourseManagerApp.h"

class ChangePasswordCommand :public Command
{
public:
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};


