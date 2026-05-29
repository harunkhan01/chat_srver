#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <pthread.h>

#include "thread_handler.h"

void* init_thread(void* arg){ 
    int err;
    struct thread_info* tinfo = arg;

    /* We wait until we receive a signal from the main process */
    

    while(1){
        err = recv(tinfo->client_fd, tinfo->msg_buf, MESSAGE_SIZE, 0);

        if (err == 0){
            printf("User has closed connection. Exiting...\n");
            pthread_exit(&(tinfo->thread_id));
        }

        if (err == -1){
            printf("Error receiving. Exiting...");
            exit(1);
        }

        printf("Client message: %s\n", tinfo->msg_buf);
    }

}