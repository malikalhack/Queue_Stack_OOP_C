/**
 * @file    stack.h
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    18/02/2022
 */

#ifndef STACK_H_
#define STACK_H_

#include "memory.h"

static uint8_t Stack_head_(Memory const * const);
static bool Stack_empty_(Memory const * const);
static void Stack_clean_(Memory * const);
static bool Stack_push_(Memory * const, uint8_t);
static uint8_t Stack_pop_(Memory * const);

typedef struct {
    Memory super;
} Stack;

void Stack_ctor(Stack * const, size_t/*, type*/);
void Stack_dctor(Stack * const);

#endif // !STACK_H_
