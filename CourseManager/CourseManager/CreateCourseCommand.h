#pragma once
#include "Command.h"

class CreateCourseCommand :public Command
{
public:
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

