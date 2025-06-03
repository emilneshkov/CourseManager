#include "UserRepository.h"
#include <fstream>
#include "Admin.h"
#include "UserFactory.h"

void UserRepository::free()
{
	for (int i = 0; i < size; i++) {
		delete users[i];
	}

	delete[] users;

	size = 0;
	capacity = 8;
	users = new User * [capacity];
}

void UserRepository::copyFrom(const UserRepository& other)
{
	users = new User * [other.capacity];
	for (int i = 0; i < other.size; i++) {
		users[i] = other.users[i]->clone();
	}

	capacity = other.capacity;
	size = other.size;
}

void UserRepository::moveFrom(UserRepository&& other)
{
	users = other.users;
	other.users = nullptr;

	capacity = other.capacity;
	size = other.size;
}

void UserRepository::resize(size_t newCapacity)
{
	capacity = newCapacity;
	User** temp = new User * [capacity];

	for (int i = 0; i < size; i++) {
		temp[i] = users[i];
	}

	delete[] users;
	users = temp;
}

UserRepository::UserRepository()
{
	capacity = 8;
	users = new User * [capacity];
	size = 0;
}

UserRepository::UserRepository(const UserRepository& other)
{
	copyFrom(other);
}

UserRepository& UserRepository::operator=(const UserRepository& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

UserRepository::UserRepository(UserRepository&& other) noexcept
{
	moveFrom(std::move(other));
}

UserRepository& UserRepository::operator=(UserRepository&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

UserRepository::~UserRepository()
{
	free();
}

void UserRepository::add(const User& user)
{
	if (size == capacity) {
		resize(capacity * 2);
	}

	users[size++] = user.clone();
}

void UserRepository::remove(size_t index)
{
	if (index >= size)
	{
		return;
	}

	std::swap(users[index], users[size - 1]);
	delete users[size - 1];
	users[size - 1] = nullptr;
	--size;
}

bool UserRepository::removeById(int userId)
{
	for (size_t i = 0; i < size; ++i) {
		if (users[i]->getId() == userId) {

			remove(i);
			return true;
		}
	}
	return false;
}

User& UserRepository::findById(int userId) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (users[i]->getId() == userId) {
			return *users[i];
		}
	}
	throw std::runtime_error("UserRepository::findById: no user with ID was found.");
}

User& UserRepository::getUserByIndex(int index)
{
	return *users[index];
}

int UserRepository::getUsersCount() const
{
	return size;
}

int UserRepository::getNewUserId() const
{
	return size;
}

void UserRepository::load(const MyString& filename)
{
	free();

	std::ifstream ifs(filename.getString(),std::ios::binary);

	if (!ifs.is_open()) {

		std::cout << "Users file \"" << filename.getString() << "\" not found. Creating a new file.\n";

		std::ofstream ofs(filename.getString(), std::ios::binary);
		ofs.close();

		Admin defaultAdmin(
			0,
			MyString("Admin"),
			MyString(""),
			MyString(""),
			MyString("0000"),
			MyVector<Message>{});

		add(defaultAdmin);

		return;
	}

	size_t size = 0;
	ifs >> size;
	ifs.ignore();

	if (size == 0) {
		Admin defaultAdmin(
			0,
			MyString("Admin"),
			MyString(""),
			MyString(""),
			MyString("0000"),
			MyVector<Message>{});

		add(defaultAdmin);

		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		User* user = UserFactory::createFromStream(ifs);

		add(*user);
	}
}

void UserRepository::save(const MyString& filename) const
{
	std::ofstream ofs(filename.getString(), std::ios::binary);

	if (!ofs.is_open()) {

		std::cout << "Users file \"" << filename.getString() << "\" not found. Creating a new file.\n";

		std::ofstream newFile(filename.getString(), std::ios::binary);
		newFile.close();

		return;
	}

	ofs << size << std::endl;

	for (size_t i = 0; i < size; i++)
	{
		users[i]->saveToFile(ofs);
	}
}
