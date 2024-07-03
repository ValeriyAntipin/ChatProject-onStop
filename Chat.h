#pragma once
#include <vector>
#include <map>
#include "User.h"
#include "Message.h"

class Chat {
private:
            std::map<std::string, User> users;
            std::vector<Message> messages;
            std::string logInUser;
public:
            bool registration(const std::string& login, const std::string& password);
            bool sign_in(const std::string& login, const std::string& password);
            void sign_out();

            bool sendMessage(const std::string& receiver, const std::string& content);
            std::vector<Message> readMessages() const;
};