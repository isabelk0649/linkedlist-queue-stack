#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Push a node into a linked list stack
 * @param STACK *sp - pointer to the stack
 * @param NODE *np - pointer to the node.
*/
void push(STACK *sp, NODE *np){

    np->next = sp->top;
    sp->top = np;
    sp->length++;

}

/*
 * Pop and return the pointer of the removed top node
 * @param STACK *sp - pointer to the stack
 * @return - the reference of the removed node and set it's next to NULL
*/
NODE *pop(STACK *sp){

    if (sp->top == NULL) {
        return NULL;

    } else {
        NODE *temp_node = sp->top;
        sp->top = sp->top->next;
        sp->length--;
        return temp_node;
    }

}

/*
 * clean the linked list stack
 */
void stack_clean(STACK *sp){

    while (sp->top != NULL) {
        NODE *temp_node = sp->top;
        sp->top = sp->top->next;
        free(temp_node);
    }
    sp->length = 0;

}
