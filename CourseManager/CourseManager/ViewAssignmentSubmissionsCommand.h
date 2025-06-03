#pragma once
#include "Command.h"

class ViewAssignmentSubmissionsCommand :public Command
{
public:
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

