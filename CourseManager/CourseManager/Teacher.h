#pragma once
#include "User.h";

class Teacher:public User
{
public:
    Teacher(int id,
        const MyString& firstName,
        const MyString& lastName,
        const MyString& email,
        const MyString& password,
        const MyVector<Message>& inbox);

    Teacher(int id, 
        const MyString& firstName, 
        const MyString& lastName,
        const MyString& defaultPass);

    User* clone() const override;
};

