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

MyString User::getRoleAsString() const {
	switch (this->getRole()) {
	case User::Role::Admin:
		return MyString("Admin");
	case User::Role::Teacher:
		return MyString("Teacher");
	case User::Role::Student:
		return MyString("Student");
	default:
		return MyString("Unknown");
	}
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
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));

	int r = static_cast<int>(role);
	ofs.write(reinterpret_cast<const char*>(&r), sizeof(r));

	auto writeString = [&](const MyString& s) {
		size_t len = s.getSize();
		ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
		ofs.write(s.getString(), len);
	};

	writeString(firstName);
	writeString(lastName);
	writeString(email);
	writeString(password);

	size_t msgCount = inbox.getSize();
	ofs.write(reinterpret_cast<const char*>(&msgCount), sizeof(msgCount));
	for (size_t i = 0; i < msgCount; ++i) {
		const Message& m = inbox[i];

		int from = m.getSenderId();
		ofs.write(reinterpret_cast<const char*>(&from), sizeof(from));

		writeString(m.getContent());

		time_t t = m.getTimestamp();
		ofs.write(reinterpret_cast<const char*>(&t), sizeof(t));
	}
}