#include "User.h"

User::User(const std::string &login, const std::string &password) : login(login), password(password) {}

std::string User::getUsername() const
{
    return login;
}

bool User::checkPassword(const std::string &password)
{
    return this->password == password;
}
