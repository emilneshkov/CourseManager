#pragma once
#include "User.h"

class UserFactory
{
public:
	static User* createFromStream(std::ifstream& ifs);
};

