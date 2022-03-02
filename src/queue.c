/**
 * @file    queue.c
 * @version 1.1.1
 * @authors Anton Chernov
 * @date    18/02/2022
 * @date    19/02/2022
 */

#include "queue.h"

static data_t Queue_head_(Data const * const);
static bool Queue_empty_(Data const * const);
static void Queue_clean_(Data * const);
static bool Queue_push_(Data * const, data_t);
static data_t Queue_pop_(Data * const);

void Queue_ctor(
    Queue * const self,
    size_t buf_size
) {
    static struct DataVtbl const vtbl = {
        &Queue_head_,
        &Queue_empty_,
        &Queue_clean_,
        &Queue_push_,
        &Queue_pop_
    };
    Data_ctor(&self->super, buf_size);
    self->super.vptr = &vtbl;
}

void Queue_dctor(Queue * const self) {
    Data_dctor(&self->super);
}

static bool Queue_push_(Data * const self, data_t item) {
    bool result = false;
    if (self->is_empty) {
        *(self->ptr + self->head) = item;
        self->is_empty = false;
        result = true;
    }
    else {
        size_t old_tail = self->tail++;
        if (self->tail >= self->buffer_size) self->tail = 0;
        if (self->tail != self->head) {
            *(self->ptr + self->tail) = item;
            result = true;
        }
        else {
            self->tail = old_tail;
            warning_print("Buffer overflow");
        }
    }
    return result;
}

static data_t Queue_pop_(Data * const self) {
    data_t result = 0;
    if (!self->is_empty) {
        if (self->tail == self->head) {
            self->is_empty = true;
            result = *(self->ptr + self->head);
        }
        else {
            result = *(self->ptr + self->head++);
            if (self->head >= self->buffer_size) self->buffer_size = 0;
        }
    }
    return result;
}

static data_t Queue_head_(Data const * const self) {
    data_t result = 0;
    if (!self->is_empty) {
        result = *(self->ptr + self->head);
    }
    return result;
}

static void Queue_clean_(Data * const self) {
    for (size_t i = 0; i < self->buffer_size; i++) {
        *(self->ptr + i) = 0;
    }
    self->head = 0;
    self->tail = 0;
    self->is_empty = true;
}

static bool Queue_empty_(Data const * const self) {
    return self->is_empty;
}
