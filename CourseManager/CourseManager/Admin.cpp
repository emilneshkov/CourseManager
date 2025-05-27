#include "Admin.h"

Admin::Admin(int id, const MyString& firstName, const MyString& lastName, const MyString& email, const MyString& password, const MyVector<Message>& inbox) : User(id, firstName, lastName, email, password, inbox, Role::Admin)
{
}
