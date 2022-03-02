/**
 * @file    stack.h
 * @version 1.0.1
 * @authors Anton Chernov
 * @date    18/02/2022
 * @date    02/03/2022
 */

#ifndef STACK_H_
#define STACK_H_

#include "data.h"

typedef struct {
    Data super;
} Stack;

void Stack_ctor(Stack * const, size_t/*, type*/);
void Stack_dctor(Stack * const);

#endif // !STACK_H_
