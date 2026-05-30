#ifndef QUEUE_H
#define QUEUE_H

struct Node {
    void* data;
    struct Node* next;
}

struct Queue {
    struct Node* front;
    struct Node* back;
    size_t size;
}

struct Queue* init_queue();
struct Node* pop_left(struct Queue* q);
void append_queue(struct Queue* q, void* data);

#endif