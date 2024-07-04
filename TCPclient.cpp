#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include "Chat.h"


void sendCommand(int sock, std::string& command){
    write(sock, command.c_str(), command.size());
}


void receiveResponse(int sock){
    char buf[1024] = {0};
    read(sock, buf, 1024);
    std::cout << buf << std::endl;
}


char buf[1024];

int main(){

    Chat chat;

    using namespace std;

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        cout << "error socket" << endl;
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        cout << "error connect" << endl;
        exit(2);
    }

    string login, password, receiver, content, action, data;

    cout << "1. Registration\n"
         << "2. Sign in\n";

    int choice = 0;
    cin >> choice;
    cin.ignore();

    if(choice == 1){
        action = "REGISTR";
        cout << "Enter your username: ";
        cin >> login;
        cout << "Enter your password: ";
        cin >> password;
        data = action + " " + login + " " + password + "\n";
        sendCommand(sock, data);
        receiveResponse(sock);
    }
    if(choice == 2){
        action = "LOGIN";
        cout << "Enter your username: ";
        cin >> login;
        cout << "Enter your password: ";
        cin >> password;
        data = action + " " + login + " " + password + "\n";
        sendCommand(sock, data);
        receiveResponse(sock);
    }
    
    while(true){
        cout << "1. Send a message" << endl;
        cout << "2. Get messages" << endl;
        cout << "3. Exit" << endl;

        cin >> choice;
        cin.ignore();

        if(choice == 1){
            action = "SEND";
            cout << "Enter receiver username: ";
            cin >> login;
            cout << "Enter message:" << endl;
            getline(cin, content);
            data = action + " " + login + " " + receiver + " " + content + "\n";
            sendCommand(sock, data);
            receiveResponse(sock);
        }

        else if(choice == 2){
            action = "GET MESSAGE";
            data = action + " " +  login + "\n";
            sendCommand(sock, data);
            receiveResponse(sock);
        }

        else if(choice == 3){
            close(sock);
            break;
        }
    }

    return 0;
}