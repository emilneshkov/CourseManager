#include "CommandFactory.h"
#include "LoginCommand.h"
#include "LogoutCommand.h"
#include "AddTeacherCommand.h"
#include "AddStudentCommand.h"
#include "RemoveUserCommand.h"
#include "MessageAllCommand.h"
#include "MailboxCommand.h"
#include "ClearMailboxCommand.h"
#include "ChangePasswordCommand.h"
#include "CreateCourseCommand.h"
#include "AddToCourseCommand.h"
#include "AddAssignmentCommand.h"
#include "MessageStudentsCommand.h"
#include "EnrollCommand.h"
#include "MessageCommand.h"
#include "SubmitAssignmentCommand.h"
#include "ViewMyGradesCommand.h"
#include "ViewAssignmentSubmissionsCommand.h"
#include "GradeAssignmentCommand.h"



Command* CommandFactory::create(const MyString& commandType)
{
	if (strcmp(commandType.getString(), "login") == 0) {
		return new LoginCommand();
	}
	else if (strcmp(commandType.getString(), "logout") == 0) {
		return new LogoutCommand();
	}
	else if (strcmp(commandType.getString(), "add_teacher") == 0) {
		return new AddTeacherCommand();
	}
	else if (strcmp(commandType.getString(), "add_student") == 0) {
		return new AddStudentCommand();
	}
	else if (strcmp(commandType.getString(), "remove_user") == 0) {
		return new RemoveUserCommand();
	}
	else if (strcmp(commandType.getString(), "message_all") == 0) {
		return new MessageAllCommand();
	}
	else if (strcmp(commandType.getString(), "mailbox") == 0) {
		return new MailboxCommand();
	}
	else if (strcmp(commandType.getString(), "clear_mailbox") == 0) {
		return new ClearMailboxCommand();
	}
	else if (strcmp(commandType.getString(), "change_password") == 0) {
		return new ChangePasswordCommand();
	}
	else if (strcmp(commandType.getString(), "create_course") == 0) {
		return new CreateCourseCommand();
	}
	else if (strcmp(commandType.getString(), "add_to_course") == 0) {
		return new AddToCourseCommand();
	}
	else if (strcmp(commandType.getString(), "assign_homework") == 0) {
		return new AddAssignmentCommand();
	}
	else if (strcmp(commandType.getString(), "message_students") == 0) {
		return new MessageStudentsCommand();
	}
	else if (strcmp(commandType.getString(), "enroll") == 0) {
		return new EnrollCommand();
	}
	else if (strcmp(commandType.getString(), "message") == 0) {
		return new MessageCommand();
	}
	else if (strcmp(commandType.getString(), "submit_assignment") == 0) {
		return new SubmitAssignmentCommand();
	}
	else if (strcmp(commandType.getString(), "view_assignment_submissions") == 0) {
		return new ViewAssignmentSubmissionsCommand();
	}
	else if (strcmp(commandType.getString(), "grades") == 0) {
		return new ViewMyGradesCommand();
	}
	else if (strcmp(commandType.getString(), "grade_assignment") == 0) {
		return new GradeAssignmentCommand();
	}
	return nullptr;
}
