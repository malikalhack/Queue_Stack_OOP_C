/**
 * @file    memory.h
 * @version 1.1.0
 * @authors Anton Chernov
 * @date    17/02/2022
 * @date    19/02/2022
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

typedef enum el_type {
    BYTE = 1,
    WORD,
    DWORD = 4,
    QWORD = 8
} type;

struct MemoryVtbl; /* Mandatory preliminary structure declaration */

typedef struct {
    struct MemoryVtbl const *vptr;
    uint8_t *ptr;
    size_t head;
    size_t tail;
    size_t buffer_size;
    //type el_size;
    bool is_empty;
} Memory;

struct MemoryVtbl {
    uint8_t (*head) (Memory const * const);
    bool    (*empty)(Memory const * const);
    void    (*clean)(Memory * const);
    bool    (*push) (Memory * const, uint8_t);
    uint8_t (*pop)  (Memory * const);
};

static uint8_t Memory_head_(Memory const * const);
static bool Memory_empty_(Memory const * const);
static bool Memory_push_(Memory * const, uint8_t);
static uint8_t Memory_pop_(Memory * const);
static void Memory_clean_(Memory * const);

void Memory_ctor(Memory * const, size_t/*, type*/);
void Memory_dctor(Memory * const);
uint8_t head(Memory const * const self);
bool empty(Memory const * const self);
void clean(Memory * const self);
bool push(Memory * const self, uint8_t item);
uint8_t pop(Memory * const self);

#endif // !MEMORY_H_
