/**
 * @file    memory.h
 * @version 1.1.1
 * @authors Anton Chernov
 * @date    17/02/2022
 * @date    02/03/2022
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define warning_print(fmt, ...) {\
        fprintf(\
            stdout,\
            "[WARNING] " fmt " in %s, Line %i\n",\
            __VA_ARGS__,\
            __FILE__,\
            __LINE__\
        );\
        fflush(stdout);\
    }

typedef uint8_t data_t;
struct DataVtbl; /* Mandatory preliminary structure declaration */

typedef struct {
    struct DataVtbl const *vptr;
    data_t *ptr;
    size_t head;
    size_t tail;
    size_t buffer_size;
    bool is_empty;
} Data;

struct DataVtbl {
    data_t  (*head) (Data const * const);
    bool    (*empty)(Data const * const);
    void    (*clean)(Data * const);
    bool    (*push) (Data * const, data_t);
    data_t  (*pop)  (Data * const);
};

void Data_ctor(Data * const, size_t);
void Data_dctor(Data * const);
data_t head(Data const * const self);
bool empty(Data const * const self);
void clean(Data * const self);
bool push(Data * const self, data_t item);
data_t pop(Data * const self);

#endif // !MEMORY_H_
