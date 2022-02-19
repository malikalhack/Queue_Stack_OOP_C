/**
 * @file    queue.h
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    18/02/2022
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "memory.h"

static uint8_t Queue_head_(Memory const * const);
static bool Queue_empty_(Memory const * const);
static void Queue_clean_(Memory * const);
static bool Queue_push_(Memory * const, uint8_t);
static uint8_t Queue_pop_(Memory * const);

typedef struct {
    Memory super;
} Queue;

void Queue_ctor(Queue * const, size_t /*, type*/);
void Queue_dctor(Queue * const);

#endif // !QUEUE_H_
