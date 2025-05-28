#include "CommandFactory.h"
#include "LoginCommand.h"
#include "LogoutCommand.h"
#include "AddTeacherCommand.h"
#include "MessageAllCommand.h"
#include "MailboxCommand.h"
#include "ClearMailboxCommand.h"

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
	else if (strcmp(commandType.getString(), "message_all") == 0) {
		return new MessageAllCommand();
	}
	else if (strcmp(commandType.getString(), "mailbox") == 0) {
		return new MailboxCommand();
	}
	else if (strcmp(commandType.getString(), "clear_mailbox") == 0) {
		return new ClearMailboxCommand();
	}
	throw new std::logic_error("Unknown type");
}
