#include "Message.h"

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
