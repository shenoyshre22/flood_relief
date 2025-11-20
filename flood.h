#ifndef FLOOD_H
#define FLOOD_H

#define MAX 100  //max queue size
#define MAX_AREAS 50  //max no of areas that we can have in the graph

//queue def
typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q); //does front=-1, rear=-1
int isFull(Queue *q); //checks queue full condition
int isEmpty(Queue *q); //checks queue empty condition
void enqueue(Queue *q, int value); //insert into queue
void dequeue(Queue *q, int num); //deletion from queue
void displayQueue(Queue *q); //print all

//graph def

typedef struct {
    int adj[MAX_AREAS][MAX_AREAS]; //adjacency matrix says whether 2 areas are connected or not (1=connected, 0=not connected)
    int numAreas; //no of areas that are in the graph rn
    int delivered[MAX_AREAS];  // 0 = not delivered, 1 = delivered
    char areaNames[MAX_AREAS][50]; //store region names (upto 49 characters)
} Graph;

void initGraph(Graph *g);
void addArea(Graph *g, char name[]); //add a node in graph
void deleteArea(Graph *g, char name[]); //remove node from graph
int findAreaIndex(Graph *g, char name[]); //find position of area 
void addConnection(Graph *g, char src[], char dest[]); //connects 2 nodes
void displayGraph(Graph *g); //print all nodes
void markDelivered(Graph *g, char name[]); //0=not delivered, 1=delivered
void dispatchPackages(Graph *g, Queue *q, char area[], int count);
void bfsShortestPath(Graph *g, char src[], char dest[]);

#endif