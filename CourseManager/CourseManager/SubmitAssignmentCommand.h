#pragma once
#include "Command.h"

class SubmitAssignmentCommand :public Command
{
public:
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

