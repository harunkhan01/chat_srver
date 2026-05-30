#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <pthread.h>

#include "thread_handler.h"

void wait(){
    /* We wait until we receive a signal from the main process */
    if (pthread_cond_wait(&cond, &mutex) != 0){
        printf("Error while requiring thread to wait\n");
        exit(1);
    }
}

void acquire_lock(){
    if (pthread_mutex_lock(&mutex) != 0){
        printf("Error while locking mutex\n");
        exit(1);
    }
}

void release_lock(){
    if (pthread_mutex_unlock(&mutex) != 0){
        printf("Error releasing lock\n");
        exit(1);
    }
}

void pull_from_queue(){
    ;
}

void handle_connection(){
    ;
}

void* init_thread(void* arg){ 
    int err;
    struct thread_info* tinfo = arg;

    while (1){
        wait();

        acquire_lock();

        pull_from_queue();

        release_lock();
        
        handle_connection();
    }

}