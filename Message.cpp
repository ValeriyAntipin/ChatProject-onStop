#include "Message.h"

Message::Message(const std::string& sender, const std::string& receiver, const std::string& content)
    : sender(sender), receiver(receiver), content(content) {}

std::string Message::getSender() const
{
    return sender;
}

std::string Message::getReceiver() const
{
    return receiver;
}

std::string Message::getContent() const
{
    return content;
}

