#include "User.h"
#include <fstream>

User::User(int id, const MyString& firstName, const MyString& lastName, const MyString& email, const MyString& password, const MyVector<Message>& inbox, Role role)
{
	this->id = id;
	this->firstName = firstName;
	this->lastName = lastName;
	this->email = email;
	this->password = password;
	this->role = role;
	this->inbox = inbox;
}

int User::getId() const {
	return id;
}

const MyString& User::getFirstName() const {
	return firstName;
}

const MyString& User::getLastName() const {
	return lastName;
}

const MyString& User::getEmail() const {
	return email;
}

const MyString& User::getPassword() const
{
	return password;
}

User::Role User::getRole() const {
	return role;
}

bool User::checkPassword(const MyString& pass) const {

	return password == pass;
}

void User::changePassword(const MyString& newPass) {
	password = newPass;
}

void User::receiveMessage(const Message& msg) {
	inbox.pushBack(msg);
}

const MyVector<Message>& User::getInbox() const {
	return inbox;
}

void User::clearInbox() {
	inbox.clear();
}

void User::saveToFile(std::ofstream& ofs) const
{
		// 1) Записваме id
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));

	// 2) Записваме role като int
	int r = static_cast<int>(role);
	ofs.write(reinterpret_cast<const char*>(&r), sizeof(r));

	// 3) Lambda за низове
	auto writeString = [&](const MyString& s) {
		size_t len = s.getSize();
		ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
		ofs.write(s.getString(), len);
		};

	// 4) Записваме личните полета
	writeString(firstName);
	writeString(lastName);
	writeString(email);
	writeString(password);

	// 5) Записваме inbox
	size_t msgCount = inbox.getSize();
	ofs.write(reinterpret_cast<const char*>(&msgCount), sizeof(msgCount));
	for (size_t i = 0; i < msgCount; ++i) {
		const Message& m = inbox[i];

		// 5.1) senderId
		int from = m.getSenderId();
		ofs.write(reinterpret_cast<const char*>(&from), sizeof(from));

		// 5.2) content
		writeString(m.getContent());

		// 5.3) timestamp (time_t)
		time_t t = m.getTimestamp();
		ofs.write(reinterpret_cast<const char*>(&t), sizeof(t));
	}
}

void User::loadFromFile(std::ifstream& ifs)
{
	MyString roleStr;

	ifs >> id
		>> roleStr
		>> firstName
		>> lastName
		>> email
		>> password
		>> inbox;  

	if (roleStr == "Admin") {
		role = Role::Admin;
	}
	else if (roleStr == "Teacher") {
		role = Role::Teacher;
	}
	else if (roleStr == "Student") {
		role = Role::Student;
	}
	else {
		throw ("Unknown user role in file: " + roleStr);
	}
}