#include "UserFactory.h"
#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include <fstream>

User* UserFactory::createFromStream(std::ifstream& ifs)
{
    int id;
    MyString role, firstName, lastName, email, password;
    MyVector<Message> inbox;

    if (!(ifs >> id >> role >> firstName >> lastName >> email >> password >> inbox)) {
        return nullptr;
    }

    User* newUser = nullptr;
    if (role == "Admin") {
        newUser = new Admin(id, firstName, lastName, email, password, inbox);
    }
    else if (role == "Teacher") {
        newUser = new Teacher(id, firstName, lastName, email, password, inbox);
    }
    else if (role == "Student") {
        newUser = new Student(id, firstName, lastName, email, password, inbox);
    }
    else {
        throw("UserFactory: Unknown role '" + role + "'");
    }

    return newUser;
}