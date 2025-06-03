#pragma once
#include "Command.h"

class EnrollCommand : public Command {
public:
    void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

