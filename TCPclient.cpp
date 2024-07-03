#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include "Chat.h"
#include "Functions.h"


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

    showMenu();
    string login, password, receiver, content, action;

    int choice = 0;
    cin >> choice;
    cin.ignore();

    while(choice != 6){
        
        switch(choice){
            
            case 1:
                action = "REGISTR";
                write(sock, action, size(action));
                cout << "Enter your username: ";
                cin >> login;
                cout << "Enter your password: ";
                cin >> password;
                write(sock, login, size(login));
                write(sock, password, size(password));

        }
    }

    cout << buf << endl;
    return 0;
}