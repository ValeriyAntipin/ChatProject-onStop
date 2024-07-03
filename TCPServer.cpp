#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include "Chat.h"

Chat chat;

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
                    if else(buf = "REGISTR"){
                        
                    }
                    send(sock, buf, bytes_read, 0);
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