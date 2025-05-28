#pragma once
#include "Command.h"

class MailboxCommand:public Command
{
public:
	void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

