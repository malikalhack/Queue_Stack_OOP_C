/**
 * @file    stack.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    18/02/2022
 */

#include "stack.h"

void Stack_ctor(
    Stack * const self,
    size_t buf_size
    //type el_size
) {
    static struct MemoryVtbl const vtbl = {
        &Stack_head_,
        &Stack_empty_,
        &Stack_clean_,
        &Stack_push_,
        &Stack_pop_
    };
    Memory_ctor(&self->super, buf_size/*, el_size*/);
    self->super.vptr = &vtbl;
}

void Stack_dctor(Stack * const self) {
    Memory_dctor(&self->super);
}

static bool Stack_push_(Memory * const self, uint8_t item) {
    bool result = false;
    if (self->is_empty) {
        *(self->ptr + self->head) = item;
        self->is_empty = false;
        result = true;
    }
    else {
        if (++self->head < self->buffer_size) {
            *(self->ptr + self->head) = item;
            result = true;
        }
        else {
            self->head = self->buffer_size - 1;
            printf(
                "[WARNING] Buffer overflow in %s, Line %i\n",
                __FILE__,
                __LINE__
            );
            fflush(stdout);
        }
    }
    return result;
}
static uint8_t Stack_pop_(Memory * const self) {
    uint8_t result = 0;
    if (!self->is_empty) {
        if (!self->head) {
            self->is_empty = true;
            result = *(self->ptr + self->head);
        }
        else result = *(self->ptr + self->head--);
    }
    return result;
}

static uint8_t Stack_head_(Memory const * const self) {
    uint8_t result = 0;
    if (!self->is_empty) {
        result = *(self->ptr + self->head);
    }
    return result;
}

static void Stack_clean_(Memory * const self) {
    for (size_t i = 0; i < self->buffer_size; i++) {
        *(self->ptr + i) = 0;
    }
    self->head = 0;
    self->is_empty = true;
}

static bool Stack_empty_(Memory const * const self) {
    return self->is_empty;
}
