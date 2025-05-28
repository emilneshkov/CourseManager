#include "Message.h"
#include <fstream>

Message::Message()
{
	this->senderId = -1;
	this->content = MyString();
	this->timestamp = time(nullptr);
}

Message::Message(int senderId, MyString content)
{
	this->senderId = senderId;
	this->content = content;
	this->timestamp = time(nullptr);
}

Message& Message::operator=(const Message& other)
{
	if (this != &other) {
		senderId = other.senderId;  
		content = other.content;  
		timestamp = other.timestamp;
	}
	return *this;
}

int Message::getSenderId() const
{
	return senderId;
}

const MyString& Message::getContent() const
{
	return content;
}

time_t Message::getTimestamp() const
{
	return timestamp;
}

std::istream& operator>>(std::istream& is, Message& message)
{
	is >> message.senderId >> message.content >> message.timestamp;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Message& message)
{
	os << message.getSenderId() << ' ' << message.getContent() << ' ' << message.getTimestamp() << '\n';
	return os;
}