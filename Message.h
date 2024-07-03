#pragma once
#include <iostream>
#include <string.h>

class Message {
private:
        std::string sender;
        std::string receiver;
        std::string content;
public:
        std::string getSender() const;
        std::string getReceiver() const;
        std::string getContent() const;
};