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

void Chat::sendMessage(const std::string& sender, const std::string& receiver, const std::string& text) {
    if (users.find(receiver) != users.end()) {
        messages.push_back(Message(sender, receiver, text));
    }
}

std::vector<Message> Chat::getMessages(const std::string& username) {
    std::vector<Message> userMessages;
    for (const auto& message : messages) {
        if (message.getReceiver() == username) {
            userMessages.push_back(message);
        }
    }
    return userMessages;
}