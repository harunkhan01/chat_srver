#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define SERVER_PORT 8443
#define SERVER_IP "10.0.0.1"

int init_server(){

    // open socket -- if raw socket then accept becomes useless
    int err; 
    int fd = socket(AF_INET, SOCK_STREAM, 0);  

    if (fd == -1){
        printf("Error opening socket. Exiting...\n");
        exit(1);
    }

    struct sockaddr_in addr;
    struct in_addr server_ip;

    if (inet_pton(AF_INET, SERVER_IP, &server_ip) != 1){
        printf("Error setting server IP address. Exiting...\n");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = SERVER_PORT;
    addr.sin_addr = server_ip; 

    socklen_t addr_len = sizeof(addr);

    // provide the socket with a name
    err = bind(fd, (struct sockaddr *)&addr, addr_len);
    if (err == -1){
        printf("Error. Value: %d\n", errno);
        exit(1); 
    }

    err = listen(fd, 10); // permit 10 requests before refusing further requests
    if (err == -1){
        printf("Error. Value: %d\n", errno);
        exit(1);
    }

    printf("Server is up and running.");

    // begin loop to track incoming requests
    while (1){
        accept(fd, )

    }
    
    

    return 0;
}