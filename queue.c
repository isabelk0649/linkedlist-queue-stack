#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "common.h"

/*
 * Enqueue a node into a queue
 * @param *qp - pointer to the queue
 * @param NODE *np - pointer to the node.
*/
void enqueue(QUEUE *qp, NODE *np){

	if (qp->front == NULL) {
		qp->front = np;
		qp->rear = np;
		np->next = NULL;

	} else {
        qp->rear->next = np;
        qp->rear = np;
        np->next = NULL;
	}
	qp->length++;
}

/*
 * Dequeue and return the pointer of the removed node.
 * @param *qp - pointer to the queue
 * @return - the reference of the removed node, and set it's next to NULL
*/
NODE *dequeue(QUEUE *qp){

	if (qp->front == NULL) {
		return NULL;

	} else {
        NODE *temp_node = qp->front;
        qp->front = qp->front->next;
        if (qp->front == NULL) {
            qp->rear = NULL; // Queue is empty
        }
        qp->length--;
        return temp_node;
	}

}

/*
 * Clean the linked list queue
*/
void queue_clean(QUEUE *qp){

    while (qp->front != NULL) {
        NODE *temp_node = qp->front;
        qp->front = qp->front->next;
        free(temp_node);
    }
    qp->rear = NULL;
    qp->length = 0;

}
