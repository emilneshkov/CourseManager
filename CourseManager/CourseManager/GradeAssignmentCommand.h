#pragma once
#include "Command.h"

class GradeAssignmentCommand : public Command {
public:
    void execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const override;
};

