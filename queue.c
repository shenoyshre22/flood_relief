#include <stdio.h>
#include "flood.h"

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Inventory full! Cannot add more packages.\n");
        return;
    }
    if (isEmpty(q)) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

void dequeue(Queue *q, int num) {
    if (isEmpty(q)) {
        printf("Inventory empty! Nothing to transport.\n");
        return;
    }

    int available = q->rear - q->front + 1;
    if (num > available) {
        printf("Only %d packages available, cannot remove %d.\n", available, num);
        return;
    }

    printf("Transporting %d packages...\n", num);
    q->front += num;

    if (q->front > q->rear) { // reset queue if empty
        initQueue(q);
    }
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Inventory empty.\n");
        return;
    }
    printf("Current inventory (%d packages): ", q->rear - q->front + 1);
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}