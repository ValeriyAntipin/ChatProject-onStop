#include "Chat.h"

Chat::Chat() : logInUser("") {}

bool Chat::registration(const std::string &login, const std::string &password)
{
    if(users.find(login) != users.end()) {
        std::cout << "login alredy used" << std::endl;
        return false;
    }
    users[login] = User(login, password);
    return true;
}

bool Chat::sign_in(const std::string &login, const std::string &password)
{
    auto it = users.find(login);
    if(it != users.end() && it->second.checkPassword(password)) {
        logInUser = login;
        return true;
    }
    std::cout << "sign_in failed" << std::endl;
    return false;
}

void Chat::sign_out()
{
    logInUser = "";
}

bool Chat::sendMessage(const std::string &receiver, const std::string &content)
{
    if(logInUser.empty() || users.find(receiver) == users.end) {
        std::cout << "User not found" << std::endl;
        return false;
    }
    messages.emplace_back(logInUser, receiver, content);
    return true;
}

std::vector<Message> Chat::readMessages() const
{
   std::vector<Message> userMessages;
   for(const auto& message : messages) {
        if(message.getReceiver() == logInUser) {
            userMessages.push_back(message);
        }
   }
   return userMessages;
}