/**
 * @file    main.c
 * @version 0.2.0
 * @authors Anton Chernov
 * @date    17/02/2022
 */

#include "stack.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define DISCARD_RETURN(f)   ((void)f)

#define STACK_LENGTH        (10)

int main() {
    Stack stack_1;

    Stack_ctor(&stack_1, STACK_LENGTH /*, BYTE*/);

    /* Added extra unit to size to check for buffer overflow */
    for (uint8_t i = 0; i < STACK_LENGTH + 1; i++) {
        DISCARD_RETURN(push(&stack_1.super, 48 + i));
    }
    printf("The front of the stack: %d. ", head(&stack_1.super));

    printf("\nThe content of the stack:\n");
    while ( !empty(&stack_1.super) ) {
        printf("%4d\n", pop(&stack_1.super));
    }
    Stack_dctor(&stack_1);

    getchar();
    return 0;
}

