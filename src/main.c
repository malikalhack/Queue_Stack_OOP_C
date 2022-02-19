/**
 * @file    main.c
 * @version 0.3.0
 * @authors Anton Chernov
 * @date    17/02/2022
 */

#include "stack.h"
#include "queue.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define DISCARD_RETURN(f)   ((void)f)

#define QUEUE_LENGTH        (10)
#define STACK_LENGTH        (10)

int main() {
    Stack stack_1;
    Queue queue_1;

    Stack_ctor(&stack_1, STACK_LENGTH /*, BYTE*/);
    Queue_ctor(&queue_1, QUEUE_LENGTH /*, BYTE*/);

    /* Added extra unit to size to check for buffer overflow */
    for (
        uint8_t i = 0, max = MAX(QUEUE_LENGTH, STACK_LENGTH);
        i < (max + 1);
        i++
    ) {
        if (i < STACK_LENGTH + 1 ) DISCARD_RETURN(push(&stack_1.super, 48 + i));
        if (i < QUEUE_LENGTH + 1) DISCARD_RETURN(push(&queue_1.super, 48 + i));
    }
    printf("The front of the stack: %d. ", head(&stack_1.super));
    printf("The front of the queue: %d\n", head(&queue_1.super));
    printf("\nThe content of the buffers:\n");
    while ( !(empty(&stack_1.super) && empty(&queue_1.super)) ) {
        if (empty(&stack_1.super)) printf("\tstack: \t\t");
        else printf("\tstack: %4d\t", pop(&stack_1.super));
        if (empty(&queue_1.super)) printf("queue:\n");
        else printf("queue: %4d\n", pop(&queue_1.super));
    }
    Stack_dctor(&stack_1);
    Queue_dctor(&queue_1);

    getchar();
    return 0;
}

