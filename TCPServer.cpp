#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include "Chat.h"

Chat chat;

void commandsClient(int client_socket){

    char buffer[1024];
    while(true){
        memset(buffer, 0, 1024);
        int bytes_read = read(client_socket, buffer, 1024);
        if(bytes_read <= 0)
            break;
        std::string command(buffer);
        std::string response;

        if(command.rfind("REGISTR ", 0) == 0) {
            size_t space_pos = command.find(' ', 8);
            std::string username = command.substr(8, space_pos - 8);
            std::string password = command.substr(space_pos + 1);
            if(chat.registration(username, password)){
                response = "Registered\n";
            }
            else{
                response = "Error registration\n";
            }
        }
        else if(command.rfind("LOGIN ", 0) == 0) {
            size_t space_pos = command.find(' ', 6);
            std::string username = command.substr(6, space_pos - 6);
            std::string password = command.substr(space_pos + 1);
            if(chat.sign_in(username, password)){
                response = "Sign in done\n";
            }
            else{
                response = "Error sign in\n";
            }
        }
        else if(command.rfind("SEND ", 0) == 0) {
            size_t space_pos1 = command.find(' ', 5);
            size_t space_pos2 = command.find(' ', space_pos1 + 1);
            std::string sender = command.substr(5, space_pos1 - 5);
            std::string receiver = command.substr(space_pos1 + 1, space_pos2 - space_pos1 - 1);
            std::string content = command.substr(space_pos2 + 1);
            chat.sendMessage(sender, receiver, content);
            response = "Message sent\n";
        }
        else if(command.rfind("GET ", 0) == 0) {
            std::string username = command.substr(13);
            std::vector<Message> messages = chat.getMessages(username);
            for (const auto& msg : messages) {
                response += msg.getSender() + ": " + msg.getContent() + "\n";
            }
            response += "END OF MESSAGES\n";
        }

        write(client_socket, response.c_str(), response.size());
    }

    close(client_socket);
}

int main() {

    using namespace std;

    struct sockaddr_in addr;
    int sock, listener;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0){
        cout << "error listener" << endl;
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = INADDR_LOOPBACK;
    if(bind(listener, (struct sockaddr *)& addr, sizeof(addr)) < 0){
        cout << "error bind" << endl;
        exit(2);
    }
    listen(listener, 4);

    while(1){

        sock = accept(listener, NULL, NULL);
        if(sock < 0){
            cout << "accept error" << endl;
            exit(3);
        }

        switch(fork()){
            case -1:
                cout << "fork error" << endl;
                break;
            case 0:
                close(listener);
                while(1){
                    bytes_read = read(sock, buf, 1024);
                    if(bytes_read <= 0)
                        break;
                    std::thread(commandsClient, sock).detach();
                }

                close(sock);
                _exit(0);
            default:
                close(sock);
        }
    }

    close(listener);
    return 0;
}