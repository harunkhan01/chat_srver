#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <pthread.h>

#define SERVER_PORT 8443
#define SERVER_IP "127.0.0.2"
#define QUEUE_CAP 5 
#define MAX_CLIENTS 10

#define MESSAGE_SIZE 256

struct thread_info {
    pthread_t thread_id;
    int       thread_num;
    int       client_fd;
    char      msg_buf[MESSAGE_SIZE];
};

struct thread_info t_info_buf[MAX_CLIENTS];
pthread_t thread_buf[MAX_CLIENTS];

static void* init_thread(void* arg){ 
    int err;
    struct thread_info* tinfo = arg;

    while(1){
        err = recv(tinfo->client_fd, tinfo->msg_buf, MESSAGE_SIZE, 0);

        if (err == 0){
            printf("User has closed connection. Exiting...\n");
            exit(1);
        }

        if (err == -1){
            printf("Error receiving. Exiting...");
            exit(1);
        }

        printf("Client message: %s\n", tinfo->msg_buf);
    }

}

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
        printf("Error on bind() invocation. Value: %d\n", errno);
        exit(1); 
    }

    err = listen(fd, QUEUE_CAP); // permit 10 requests before refusing further requests
    if (err == -1){
        printf("Error. Value: %d\n", errno);
        exit(1);
    }

    printf("Server is up and running.\n");

    // begin loop to track incoming requests
    int client_id;
    int curr_thread = 0;
    struct in_addr client_ip;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while(1){
        client_id = accept(fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_id == -1){
            printf("Error. Value: %d\n", errno);
            exit(1);
        }
        printf("Client successfully connected!\n");

        if (curr_thread == MAX_CLIENTS){
            printf("At max capacity. Dropping connection...\n");
            exit(1);
        }

        /* Spawn a thread to negotiate with client */
        pthread_t client_thread;
        thread_buf[curr_thread] = client_thread;
        t_info_buf[curr_thread].thread_id = thread_buf[curr_thread];
        t_info_buf[curr_thread].thread_num = curr_thread;
        t_info_buf[curr_thread].client_fd = client_id;

        err = pthread_create(&thread_buf[curr_thread], NULL, &init_thread, &t_info_buf[curr_thread]); 
        if (err != 0){
            printf("Failure to spawn thread. Client dropped...\n");
        }
        ++curr_thread;

    }

    return 0;
}

int main() {
    init_server();
}