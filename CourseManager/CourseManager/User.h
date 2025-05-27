#pragma once
#include "MyString.h";
#include "MyVector.hpp";
#include "Message.h";

class User
{
public:
	enum class Role { Admin, Teacher, Student };

	User(int id, const MyString& firstName,
		const MyString& lastName,
		const MyString& email,
		const MyString& password,
		const MyVector<Message>& inbox,
		Role role);

	virtual ~User() = default;

	int getId() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getEmail() const;
	const MyString& getPassword() const;
	Role getRole() const;

	bool checkPassword(const MyString& pass) const;
	void changePassword(const MyString& newPass);

	void receiveMessage(const Message& msg);
	const MyVector<Message>& getInbox() const;
	void clearInbox();

	virtual void saveToFile(std::ofstream& ofs)const;
	virtual void loadFromFile(std::ifstream& ifs);

private:
	int id;
	MyString firstName;
	MyString lastName;
	MyString email;
	MyString password;
	MyVector<Message> inbox;
	Role role;
};

