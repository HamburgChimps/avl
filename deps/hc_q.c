#include "hc_q.h"

hc_q* hc_q_init(size_t init_capacity) {
    hc_q* q = malloc(sizeof(hc_q));

    q->data = malloc(sizeof(void*) * init_capacity);
    q->size = 0;
    q->offset = 0;
    q->potential_size = init_capacity;
    return q;
}

void hc_q_enqueue(hc_q* q, void* data) {
    if (q->size + q->offset == q->potential_size) {
        q->potential_size *= 2;
        q->data = realloc(q->data, sizeof(void*) * q->potential_size);
    }

    *(q->data + q->size + q->offset) = data;
    ++q->size;
}

void* hc_q_dequeue(hc_q* q) {
    if (q->size == 0) return NULL;

    void* el = *(q->data + q->offset);
    --q->size;
    ++q->offset;

    return el;
}

void hc_q_destroy(hc_q** q) {
    free((*q)->data);
    free(*q);

    *q = NULL;
}
