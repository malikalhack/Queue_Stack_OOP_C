/**
 * @file    stack.c
 * @version 1.1.1
 * @authors Anton Chernov
 * @date    18/02/2022
 * @date    02/03/2022
 */

#include "stack.h"

static uint8_t Stack_head_(Data const * const);
static bool Stack_empty_(Data const * const);
static void Stack_clean_(Data * const);
static bool Stack_push_(Data * const, uint8_t);
static uint8_t Stack_pop_(Data * const);

void Stack_ctor(
    Stack * const self,
    size_t buf_size
    //type el_size
) {
    static struct DataVtbl const vtbl = {
        &Stack_head_,
        &Stack_empty_,
        &Stack_clean_,
        &Stack_push_,
        &Stack_pop_
    };
    Data_ctor(&self->super, buf_size/*, el_size*/);
    self->super.vptr = &vtbl;
}

void Stack_dctor(Stack * const self) {
    Data_dctor(&self->super);
}

static bool Stack_push_(Data * const self, uint8_t item) {
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
            warning_print("Buffer overflow");
        }
    }
    return result;
}
static uint8_t Stack_pop_(Data * const self) {
    uint8_t result = 0;
    if (!self->is_empty) {
        if (!self->head) {
            self->is_empty = true;
            result = *self->ptr;
        }
        else result = *(self->ptr + self->head--);
    }
    return result;
}

static uint8_t Stack_head_(Data const * const self) {
    uint8_t result = 0;
    if (!self->is_empty) {
        result = *(self->ptr + self->head);
    }
    return result;
}

static void Stack_clean_(Data * const self) {
    for (size_t i = 0; i < self->buffer_size; i++) {
        *(self->ptr + i) = 0;
    }
    self->head = 0;
    self->is_empty = true;
}

static bool Stack_empty_(Data const * const self) {
    return self->is_empty;
}
