#ifndef FLOOD_H
#define FLOOD_H

#define MAX 100  // maximum queue size
#define MAX_AREAS 50  // maximum number of areas in graph

// ================= QUEUE =================

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, int value);
void dequeue(Queue *q, int num);
void displayQueue(Queue *q);

// ================= GRAPH =================

typedef struct {
    int adj[MAX_AREAS][MAX_AREAS];
    int numAreas;
    int delivered[MAX_AREAS];  // 0 = not delivered, 1 = delivered
    char areaNames[MAX_AREAS][50];
} Graph;

void initGraph(Graph *g);
void addArea(Graph *g, char name[]);
void deleteArea(Graph *g, char name[]);
int findAreaIndex(Graph *g, char name[]);
void addConnection(Graph *g, char src[], char dest[]);
void displayGraph(Graph *g);
void markDelivered(Graph *g, char name[]);

#endif