#include "UserFactory.h"
#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include <fstream>

User* UserFactory::createFromStream(std::ifstream& ifs)
{
	if (!ifs.good()) return nullptr;

	int id;
	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
	if (!ifs) {
		return nullptr;
	}

	int roleInt;
	ifs.read(reinterpret_cast<char*>(&roleInt), sizeof(roleInt));
	if (!ifs) {
		return nullptr;
	}

	User::Role role = static_cast<User::Role>(roleInt);

	auto readString = [&](MyString& s) {
		size_t len;
		ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
		if (!ifs) {
			return false;
		}

		s.clear();
		s.reserve(len);
		char* buf = new char[len];
		ifs.read(buf, len);
		if (!ifs) {
			delete[] buf; return false;
		}

		for (size_t i = 0; i < len; ++i) {
			s.pushBack(buf[i]);
		}

		delete[] buf;
		return true;

		};

	MyString firstName, lastName, email, password;
	if (!readString(firstName)) {
		return nullptr;
	}
	if (!readString(lastName))  {
		return nullptr;
	}
	if (!readString(email))     {
		return nullptr;
	}
	if (!readString(password))  {
		return nullptr;
	}


	size_t msgCount;
	ifs.read(reinterpret_cast<char*>(&msgCount), sizeof(msgCount));
	if (!ifs) {
		return nullptr;
	}

	MyVector<Message> inbox;
	inbox.reserve(msgCount);

	for (size_t i = 0; i < msgCount; ++i) {

		int senderId;
		ifs.read(reinterpret_cast<char*>(&senderId), sizeof(senderId));
		if (!ifs) {
			return nullptr;
		}

		MyString content;
		if (!readString(content)) {
			return nullptr;
		}

		time_t t;
		ifs.read(reinterpret_cast<char*>(&t), sizeof(t));
		if (!ifs) {
			return nullptr;
		}

		Message message(senderId, content, t);
		inbox.pushBack(message);
	}

	switch (role) {
	case User::Role::Admin:
		return new Admin(id, firstName, lastName, email, password, inbox);
	case User::Role::Teacher:
		return new Teacher(id, firstName, lastName, email, password, inbox);
	case User::Role::Student:
		return new Student(id, firstName, lastName, email, password, inbox);
	default:
		return nullptr;
	}
}