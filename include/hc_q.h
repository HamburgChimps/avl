#ifndef HC_Q_H
#define HC_Q_H

#include <stdlib.h>

typedef struct hc_q {
    void** data;
    size_t size;
    size_t potential_size;
    int offset;
} hc_q;

hc_q* hc_q_init(size_t init_capacity);

void hc_q_enqueue(hc_q* q, void* data);
void* hc_q_dequeue(hc_q* q);

void hc_q_destroy(hc_q** q);

#endif