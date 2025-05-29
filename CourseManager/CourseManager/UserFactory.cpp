#include "UserFactory.h"
#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include <fstream>

User* UserFactory::createFromStream(std::ifstream& ifs)
{
    if (!ifs.good()) return nullptr;

    // 1) Прочитаме id
    int id;
    ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
    if (!ifs) return nullptr;

    // 2) Прочитаме role
    int roleInt;
    ifs.read(reinterpret_cast<char*>(&roleInt), sizeof(roleInt));
    if (!ifs) return nullptr;
    User::Role role = static_cast<User::Role>(roleInt);

    // 3) Ламбда за четене на MyString (content)
    auto readString = [&](MyString& s) {
        size_t len;
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (!ifs) return false;
        s.clear();
        s.reserve(len);
        char* buf = new char[len];
        ifs.read(buf, len);
        if (!ifs) { delete[] buf; return false; }
        for (size_t i = 0; i < len; ++i) s.pushBack(buf[i]);
        delete[] buf;
        return true;
        };

    // 4) Прочитаме текстовите полета
    MyString firstName, lastName, email, password;
    if (!readString(firstName)) return nullptr;
    if (!readString(lastName))  return nullptr;
    if (!readString(email))     return nullptr;
    if (!readString(password))  return nullptr;

    // 5) Прочитаме inbox
    size_t msgCount;
    ifs.read(reinterpret_cast<char*>(&msgCount), sizeof(msgCount));
    if (!ifs) return nullptr;

    MyVector<Message> inbox;
    inbox.reserve(msgCount);

    for (size_t i = 0; i < msgCount; ++i) {
        // 1) Прочитаме senderId
        int senderId;
        ifs.read(reinterpret_cast<char*>(&senderId), sizeof(senderId));
        if (!ifs) return nullptr;

        // 2) Прочитаме content
        MyString content;
        if (!readString(content)) return nullptr;

        // 3) Прочитаме timestamp
        time_t t;
        ifs.read(reinterpret_cast<char*>(&t), sizeof(t));
        if (!ifs) return nullptr;

        // 4) Създаваме съобщението през конструктора и го добавяме
        Message message(senderId, content, t);
        inbox.pushBack(message);
    }

    // 6) Създаваме обекта според ролята
    switch (role) {
    case User::Role::Admin:
        return new Admin(id, firstName, lastName, email, password, inbox);
    case User::Role::Teacher:
        return new Teacher(id, firstName, lastName, email, password, inbox);
    case User::Role::Student:
        return new Student(id, firstName, lastName, email, password, inbox);
    default:
        return nullptr;
    }
}