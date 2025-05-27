
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"

Admin::Admin(int id, const MyString& firstName, const MyString& lastName, const MyString& email, const MyString& password, const MyVector<Message>& inbox) : User(id, firstName, lastName, email, password, inbox, Role::Admin)
{
}

User* Admin::clone() const
{
    return new Admin(*this);
}

int Admin::addTeacher(const MyString& firstName, const MyString& lastName, const MyString& defaultPass, UserRepository& userRepo)
{
	int newId = userRepo.getNewUserId();

	Teacher newTeacher(newId, firstName, lastName, defaultPass);

	userRepo.add(newTeacher);

	return newId;
}

int Admin::addStudent(const MyString& firstName, const MyString& lastName, const MyString& defaultPass, UserRepository& userRepo)
{
	int newId = userRepo.getNewUserId();

	Student newStudent (newId, firstName, lastName, defaultPass);

	userRepo.add(newStudent);

	return newId;
}

void Admin::messageAll(const MyString& content, UserRepository& userRepo)
{
	Message newMessage(this->getId(), content);

	for (size_t i = 0; i < userRepo.getUsersCount(); i++)
	{
		userRepo.getUserByIndex(i).receiveMessage(newMessage);
	}
}

const MyVector<Message>& Admin::viewInboxOf(int userId, UserRepository& userRepo) const
{
	User& user = userRepo.findById(userId);
	return user.getInbox();
}