#pragma once
#include <vector>
#include <map>
#include "User.h"
#include "Message.h"

class Chat {
private:
            std::map<std::string, User> users;
            std::vector<Message> messages;
public:
            bool registration(const std::string& login, const std::string& password);
            bool sign_in(const std::string& login, const std::string& password);
            void sendMessage(const std::string& sender, const std::string& receiver, const std::string& text);
            std::vector<Message> getMessages(const std::string& username);
};