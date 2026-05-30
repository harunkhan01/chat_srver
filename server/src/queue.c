/* 
Implementation of a queue


*/

#include <stdlib.h>

#include "queue.h"

struct Queue* init_queue(){
    struct Queue* q = malloc(sizeof(struct Queue));
    q->front = NULL;
    q->back = NULL;
    q->size = 0;

    return q;
}

struct Node* pop_left(struct Queue* q){
    if (q->size != 0){
        struct Node* front = q->front;
        q->front = q->front->next;
        q->size--;
        return front;
    }

    printf("Error! Trying to pop from empty queue\n");
    exit(1);
}

void append_queue(struct Queue* q, void* data){
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;

    if (q->back != NULL){
        q->back->next = new_node;
        q->back = new_node;
    } else {
        q->front = new_node;
        q->back = new_node;
    }

    q->size++;
}