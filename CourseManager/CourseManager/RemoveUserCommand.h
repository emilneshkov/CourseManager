#include "Command.h"
#include "CourseManagerApp.h"


class RemoveUserCommand : public Command {
public:
    void execute(const MyVector<MyString>& arguments,CourseManagerApp& courseApp) const override;
};
