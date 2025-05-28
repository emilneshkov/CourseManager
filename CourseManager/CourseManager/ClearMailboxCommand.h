#pragma once
#include "Command.h"
class ClearMailboxCommand :public Command
{
public:
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};


