#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <pthread.h>

#include "queue.h"
#include "server.h"
#include "thread_handler.h"

struct Queue* work_q;
struct thread_info t_info_buf[MAX_THREADS];
pthread_t thread_buf[MAX_THREADS];

/* Global variables for threads to see */
pthread_cond_t cond; 
pthread_mutex_t mutex; 

int init_thread_pool(){
    pthread_t client_thread;

    for (int i=0; i < MAX_THREADS; ++i){
        thread_buf[i] = client_thread;
        t_info_buf[i].thread_id = thread_buf[i];
        t_info_buf[i].thread_num = i;
        t_info_buf[i].client_fd = client_id;

        err = pthread_create(&thread_buf[i], NULL, init_thread, &t_info_buf[i]); 
        if (err != 0){
            printf("Failure to initialize thread.\n");
            return err;
        }
    }
    
    return 0;
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

    work_q = init_queue();
    init_thread_pool();

    err = listen(fd, QUEUE_CAP); // permit 10 requests before refusing further requests
    if (err == -1){
        printf("Error. Value: %d\n", errno);
        exit(1);
    }

    printf("Server is up and running.\n");

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

        if (curr_thread == MAX_THREADS){
            printf("At max capacity. Connection rejected...\n");
            continue;
        }

        /* Signal to thread to respond to client */

        /* Spawn a thread to negotiate with client */
        ++curr_thread;

    }

    return 0;
}

int main() {
    init_server();
}