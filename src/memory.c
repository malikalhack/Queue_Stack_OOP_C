/**
 * @file    memory.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    17/02/2022
 */

#include "memory.h"

void Memory_ctor(
    Memory * const self,
    size_t buf_size
    //type el_size
) {
    static struct MemoryVtbl const vtbl = {
        &Memory_head_,
        &Memory_empty_,
        &Memory_clean_,
        &Memory_push_,
        &Memory_pop_
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

void Memory_dctor(Memory * const self) {
    if (self->ptr) free(self->ptr);
}

bool push(Memory * const self, uint8_t item) {
    return (*self->vptr->push)(self, item);
}

uint8_t pop(Memory * const self) {
    return (*self->vptr->pop)(self);
}

uint8_t head(Memory const * const self) {
    return (*self->vptr->head)(self);
}

void clean(Memory * const self) {
    (*self->vptr->clean)(self);
}

bool empty(Memory const * const self) {
    return (*self->vptr->empty)(self);
}

static bool Memory_push_(Memory * const self, uint8_t item) {
    assert(0); /* purely-virtual function should never be called */
    return false; /* to avoid compiler warnings */
}

static uint8_t Memory_pop_(Memory * const self) {
    assert(0); /* purely-virtual function should never be called */
    return 0; /* to avoid compiler warnings */
}

static uint8_t Memory_head_(Memory const * const self) {
    assert(0); /* purely-virtual function should never be called */
    return 0; /* to avoid compiler warnings */
}

static void Memory_clean_(Memory * const self) {
    assert(0); /* purely-virtual function should never be called */
}

static bool Memory_empty_(Memory const * const self) {
    assert(0); /* purely-virtual function should never be called */
    return false; /* to avoid compiler warnings */
}

