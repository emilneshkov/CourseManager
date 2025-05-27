#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "CourseManagerApp.h"

class Command
{
public:
	virtual void execute(const MyVector<MyString>& arguments,CourseManagerApp& courseApp) const = 0;
	virtual ~Command() = default;
};

