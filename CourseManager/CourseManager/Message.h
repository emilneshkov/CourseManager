#pragma once
#include "MyString.h";
#include "ctime";

class Message
{
	int senderId;
	MyString content;
	time_t timestamp;

public:
	Message();
	Message(int senderId, MyString content);
	Message& operator=(const Message& other);

	int getSenderId() const;
	const MyString& getContent() const;
	time_t getTimestamp() const;

	friend std::istream& operator>>(std::istream& is, Message& message);
};
std::ostream& operator<<(std::ostream& os, const Message& message);


