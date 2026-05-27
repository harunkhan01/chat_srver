#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#define MESSAGE_SIZE 256

struct thread_info {
    pthread_t thread_id;
    int       thread_num;
    int       client_fd;
    char      msg_buf[MESSAGE_SIZE];
};

void* init_thread(void* arg);

#endif