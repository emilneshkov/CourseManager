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
	MyString role;

	switch (this->getRole()) {
	case User::Role::Admin:   role = "Admin"; break;
	case User::Role::Teacher: role = "Teacher"; break;
	case User::Role::Student: role = "Student"; break;
	}

	ofs << id << ' '
		<< role << ' '
		<< firstName << ' '
		<< lastName << ' '
		<< email << ' '
		<< password << ' '
		<< inbox
		<< '\n';
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