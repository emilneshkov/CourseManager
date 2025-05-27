#include "CommandFactory.h"
#include "LoginCommand.h"

Command* CommandFactory::create(const MyString& commandType)
{
	if (strcmp(commandType.getString(), "login") == 0) {
		return new LoginCommand();
	}

	throw new std::logic_error("Unknown type");
}
