#include <stdio.h>
#include <string.h>
#include "flood.h"


void initGraph(Graph *g) {
    g->numAreas = 0;
    for (int i = 0; i < MAX_AREAS; i++) {
        g->delivered[i] = 0;
        for (int j = 0; j < MAX_AREAS; j++)
            g->adj[i][j] = 0;
    }
}

int findAreaIndex(Graph *g, char name[]) {
    for (int i = 0; i < g->numAreas; i++) {
        if (strcmp(g->areaNames[i], name) == 0)
            return i;
    }
    return -1;
}

void addArea(Graph *g, char name[]) {
    if (g->numAreas >= MAX_AREAS) {
        printf("Max areas reached.\n");
        return;
    }
    if (findAreaIndex(g, name) != -1) {
        printf("Area already exists.\n");
        return;
    }

    strcpy(g->areaNames[g->numAreas], name);
    g->delivered[g->numAreas] = 0;
    g->numAreas++;

    printf("Area '%s' added.\n", name);
}

void deleteArea(Graph *g, char name[]) {
    int idx = findAreaIndex(g, name);
    if (idx == -1) {
        printf("Area not found.\n");
        return;
    }

    for (int i = idx; i < g->numAreas - 1; i++) //we are shifting rows from here
        for (int j = 0; j < g->numAreas; j++)
            g->adj[i][j] = g->adj[i + 1][j];

    //we are shifting columns from here
    for (int j = idx; j < g->numAreas - 1; j++)
        for (int i = 0; i < g->numAreas; i++)
            g->adj[i][j] = g->adj[i][j + 1];

    //...
    for (int i = idx; i < g->numAreas - 1; i++) {
        strcpy(g->areaNames[i], g->areaNames[i + 1]);
        g->delivered[i] = g->delivered[i + 1];
    }

    g->numAreas--;

    printf("Area '%s' deleted.\n", name);
}

void addConnection(Graph *g, char src[], char dest[]) {
    int i = findAreaIndex(g, src);
    int j = findAreaIndex(g, dest);

    if (i == -1 || j == -1) {
        printf("Invalid areas.\n");
        return;
    }

    g->adj[i][j] = g->adj[j][i] = 1;

    printf("Connection added between %s and %s.\n", src, dest);
}


void displayGraph(Graph *g) {
    if (g->numAreas == 0) {
        printf("No areas.\n");
        return;
    }

    printf("\nAREAS:\n");
    for (int i = 0; i < g->numAreas; i++) {
        printf("%d. %s\n", i + 1, g->areaNames[i]);
    }

    printf("\nADJACENCY MATRIX:\n");

    printf("      "); //space between nos
    for (int i = 0; i < g->numAreas; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < g->numAreas; i++) {

        //row
        printf("%d  |  ", i + 1);

        for (int j = 0; j < g->numAreas; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

void markDelivered(Graph *g, char name[]) {
    int idx = findAreaIndex(g, name);
    if (idx == -1) {
        printf("Area not found.\n");
        return;
    }
    g->delivered[idx] = 1;
    printf("Area '%s' marked as delivered.\n", name);
}

void dispatchPackages(Graph *g, Queue *q, char area[], int count) {
    int idx = findAreaIndex(g, area);

    if (idx == -1) {
        printf("Invalid area.\n");
        return;
    }

    if (isEmpty(q)) {
        printf("No packages in inventory.\n");
        return;
    }

    printf("Dispatching %d packages to %s...\n", count, area);

    dequeue(q, count);
    markDelivered(g, area);
}

void bfsShortestPath(Graph *g, char src[], char dest[]) {
    int srcIndex = findAreaIndex(g, src);
    int destIndex = findAreaIndex(g, dest);
    
    if (srcIndex == -1 || destIndex == -1) {
        printf("Source or destination area not found.\n");
        return;
    }
    
    if (srcIndex == destIndex) {
        printf("Shortest path from %s to %s: %s (distance: 0)\n", src, dest, src);
        return;
    }

    
    int visited[MAX_AREAS] = {0};
    int distance[MAX_AREAS] = {0};
    int parent[MAX_AREAS] = {-1};
    Queue q;
    initQueue(&q);
    visited[srcIndex] = 1;
    enqueue(&q, srcIndex);
    
    int found = 0;
    while (!isEmpty(&q) && !found) {
        int current = q.items[q.front];
        dequeue(&q, 1);
        
        printf(" Exploring from %s (index %d)\n", g->areaNames[current], current);
        

        for (int i = 0; i < g->numAreas; i++) {
            if (g->adj[current][i] == 1 && !visited[i]) {
                printf(" Found connection %s -> %s\n", g->areaNames[current], g->areaNames[i]);
                visited[i] = 1;
                distance[i] = distance[current] + 1;
                parent[i] = current;
                
                if (i == destIndex) {
                    found = 1;
                    break;
                }
                
                enqueue(&q, i);
            }
        }
    }
    
    if (!found) {
        printf("No path found from %s to %s.\n", src, dest);
    } else {
        int path[MAX_AREAS];
        int pathLength = 0;
        int current = destIndex;
        
        while (current != -1) {
            path[pathLength++] = current;
            current = parent[current];
        }
        
        printf("Shortest path from %s to %s (distance: %d): ", src, dest, distance[destIndex]);
        for (int i = pathLength - 1; i >= 0; i--) {
            printf("%s", g->areaNames[path[i]]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}

//end of graph.c