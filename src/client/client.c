#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define CLIENT_PORT 8440 
#define CLIENT_IP "127.0.0.1"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8443

int init_client(){

    // open socket -- if raw socket then accept becomes useless
    int err; 
    int fd = socket(AF_INET, SOCK_STREAM, 0);  

    if (fd == -1){
        printf("Error opening socket. Exiting...\n");
        exit(1);
    }

    struct sockaddr_in addr;
    struct in_addr client_ip;

    if (inet_pton(AF_INET, CLIENT_IP, &client_ip) != 1){
        printf("Error setting client ip address. Exiting...\n");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = CLIENT_PORT;
    addr.sin_addr = client_ip; 

    socklen_t addr_len = sizeof(addr);

    // provide the socket with a name
    err = bind(fd, (struct sockaddr *)&addr, addr_len);
    if (err == -1){
        printf("Error on bind() invocation. Value: %d\n", errno);
        exit(1); 
    }

    /* Initialize server address and port */
    struct sockaddr_in server_addr;
    struct in_addr server_ip;
    if (inet_pton(AF_INET, SERVER_IP, &server_ip) != 1){
        printf("Error setting up server ip address. Exiting...\n");
        exit(1);
    }
    server_addr.sin_port = SERVER_PORT;
    server_addr.sin_addr = server_ip;
    server_addr.sin_family = AF_INET; 

    socklen_t server_addr_len = sizeof(server_addr);

    err = connect(fd, (struct sockaddr *)&server_addr, server_addr_len);
    if (err == -1){
        printf("Error connecting to server. Exiting...\n");
        exit(1);
    }else {
        printf("Successfully connected to the server! Exiting...\n");
        exit(1);
    }

    return 0;
}

int main(){
    init_client();
}