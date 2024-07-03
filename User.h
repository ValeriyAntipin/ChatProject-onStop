#pragma once
#include <iostream>
#include <string.h>

class User {
private:
        std::string login;
        std::string password;
public:
        User(const std::string& login, const std::string& password);
        std::string getUsername() const;
        bool checkPassword(const std::string& password);
};