#pragma once
#include "User.h"

class UserRepository
{
	User** users;
	size_t capacity;
	size_t size;

	void free();
	void copyFrom(const UserRepository& other);
	void moveFrom(UserRepository&& other);
	void resize(size_t newCapacity);

public:
	UserRepository();
	UserRepository(const UserRepository& other);
	UserRepository& operator=(const UserRepository& other);

	UserRepository(UserRepository&& other)noexcept;
	UserRepository& operator=(UserRepository&& other)noexcept;

	~UserRepository();

	void add(const User& user);
	void remove(size_t index);

	User& findById(int userId)const;
	User& getUserByIndex(int index);

	int getUsersCount() const;
	int getNewUserId()const;

	void load(const MyString& filename);
	void save(const MyString& filename) const;
};