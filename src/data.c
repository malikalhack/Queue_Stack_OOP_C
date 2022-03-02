/**
 * @file    memory.c
 * @version 1.0.1
 * @authors Anton Chernov
 * @date    17/02/2022
 * @date    02/03/2022
 */

#include "data.h"

static uint8_t head_(Data const * const);
static bool empty_(Data const * const);
static bool push_(Data * const, uint8_t);
static uint8_t pop_(Data * const);
static void clean_(Data * const);

void Data_ctor(
    Data * const self,
    size_t buf_size
    //type el_size
) {
    static struct DataVtbl const vtbl = {
        &head_,
        &empty_,
        &clean_,
        &push_,
        &pop_
    };
    self->ptr = calloc(buf_size + 1, BYTE /*el_size*/);
    assert(self->ptr);
    self->vptr = &vtbl; /* "hook" the vptr to the vtbl */
    self->buffer_size = buf_size;
    //self->el_size = el_size;
    self->head = 0;
    self->tail = 0;
    self->is_empty = true;
}

void Data_dctor(Data * const self) {
    if (self->ptr) {
        free(self->ptr);
        self->ptr = NULL;
    }
}

bool push(Data * const self, uint8_t item) {
    return (*self->vptr->push)(self, item);
}

uint8_t pop(Data * const self) {
    return (*self->vptr->pop)(self);
}

uint8_t head(Data const * const self) {
    return (*self->vptr->head)(self);
}

void clean(Data * const self) {
    (*self->vptr->clean)(self);
}

bool empty(Data const * const self) {
    return (*self->vptr->empty)(self);
}

static bool push_(Data * const self, uint8_t item) {
    assert(0); /* purely-virtual function should never be called */
    return false; /* to avoid compiler warnings */
}

static uint8_t pop_(Data * const self) {
    assert(0); /* purely-virtual function should never be called */
    return 0; /* to avoid compiler warnings */
}

static uint8_t head_(Data const * const self) {
    assert(0); /* purely-virtual function should never be called */
    return 0; /* to avoid compiler warnings */
}

static void clean_(Data * const self) {
    assert(0); /* purely-virtual function should never be called */
}

static bool empty_(Data const * const self) {
    assert(0); /* purely-virtual function should never be called */
    return false; /* to avoid compiler warnings */
}

