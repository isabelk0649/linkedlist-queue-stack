#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

/*
 * Convert infix expression string to postfix expression represented by queue data structure.
 * @param infixstr - string of infix expression.
 * @return - postfix expression in queue of QUEUE type.
*/
QUEUE infix_to_postfix(char *infixstr) {

    char *p = infixstr;
    QUEUE queue = {0}; // result postfix expression in queue
    STACK stack = {0}; // auxiliary stack
    int sign = 1, num = 0;

    while (*p) { // expression string traversal
        if (*p == '-' && (p == infixstr || *(p - 1) == '(')) { // get the sign of an operand
            sign = -1;

        } else if (get_type(*p) == 0) { // namely *p is digit character, action: use horner’s algorithm to get the operand
            num = *p - '0';
            while ((*(p + 1) >= '0' && *(p + 1) <= '9')) {
                num = num * 10 + *(p + 1) - '0';
                p++;
            }
            enqueue(&queue, new_node(sign * num, 0));
            sign = 1;

        } else if (get_type(*p) == 1) { // namely *p is an operator character
            while (stack.top && get_priority(stack.top->data) >= get_priority(*p)) {
                enqueue(&queue, pop(&stack));
            }
            push(&stack, new_node(*p, 1));

        } else if (get_type(*p) == 2) { // *p == '('
            push(&stack, new_node(*p, 2));

        } else if (get_type(*p) == 3) { // *p == ')'
            while (stack.top && stack.top->data != '(') {
                enqueue(&queue, pop(&stack));
            }
            pop(&stack); // Discard '('
        } // else ignore
        p++; // move to next character
    }

    // Finally, pop each node and insert it to queue
    while (stack.top) {
        enqueue(&queue, pop(&stack));
    }

    return queue;
}


/*
 * Evaluate and return the value postfix expression passed by queue.
 * @parame queue - postfix expression in queue of QUEUE type.
 ^ @return - value of postfix expression
*/
int evaluate_postfix(QUEUE queue) {

    NODE *p = queue.front;
    STACK stack = {0}; // auxiliary stack for postfix evaluation
    int type = 0;

    while (p) { // traverse the queue linked list
        type = p->type;

        if (type == 0) { // operand
            push(&stack, new_node(p->data, 0));

        } else if (type == 1) { // operator
            int operator_char = p->data;

            if (operator_char == '+') {
                // Addition
                int operand2_data = pop(&stack)->data;
                int operand1_data = pop(&stack)->data;
                push(&stack, new_node(operand1_data + operand2_data, 0));

            } else if (operator_char == '-') {
                // Subtraction
                int operand2_data = pop(&stack)->data;
                int operand1_data = pop(&stack)->data;
                push(&stack, new_node(operand1_data - operand2_data, 0));

            } else if (operator_char == '*') {
                // Multiplication
                int operand2_data = pop(&stack)->data;
                int operand1_data = pop(&stack)->data;
                push(&stack, new_node(operand1_data * operand2_data, 0));

            } else if (operator_char == '/') {
                // Division
                int operand2_data = pop(&stack)->data;
                int operand1_data = pop(&stack)->data;
                push(&stack, new_node(operand1_data / operand2_data, 0));
            }
        }
        p = p->next;
    }

    if (stack.top == NULL) {
        // Handle error: empty stack after evaluation
        printf("Error: Empty stack after evaluation\n");
        return 0;
    }

    int result = stack.top->data;
    stack_clean(&stack);
    return result;
}


/*
 * Evaluate and return the value of infix expression passed by string infixstr,
 * using infix_to_postfix() and evaluate_postfix() functions.
 * @param infixstr - string of infix expression.
 * @return - value of the infix expression.
*/
int evaluate_infix(char *infixstr){

    QUEUE postfix_expr = infix_to_postfix(infixstr);
    int result = evaluate_postfix(postfix_expr);
    return result;

}

