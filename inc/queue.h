/**
 * @file    queue.h
 * @version 1.0.1
 * @authors Anton Chernov
 * @date    18/02/2022
 * @date    02/03/2022
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "data.h"

typedef struct {
    Data super;
} Queue;

void Queue_ctor(Queue * const, size_t);
void Queue_dctor(Queue * const);

#endif // !QUEUE_H_
