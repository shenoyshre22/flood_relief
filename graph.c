#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "flood.h"

// ----------------------------
// Helper: case-insensitive compare
// ----------------------------
int strCaseCmp(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b))
            return tolower(*a) - tolower(*b);
        a++; 
        b++;
    }
    return *a - *b;
}

// ----------------------------
// Initialize Graph
// ----------------------------
void initGraph(Graph *g) {
    g->numAreas = 0;

    for (int i = 0; i < MAX_AREAS; i++) {
        g->delivered[i] = 0;
        for (int j = 0; j < MAX_AREAS; j++)
            g->adj[i][j] = 0;
    }
}

// ----------------------------
// Find area index (case-insensitive)
// ----------------------------
int findAreaIndex(Graph *g, char name[]) {
    for (int i = 0; i < g->numAreas; i++) {
        if (strCaseCmp(g->areaNames[i], name) == 0)
            return i;
    }
    return -1;
}

// ----------------------------
// Add new area
// ----------------------------
void addArea(Graph *g, char name[]) {
    if (g->numAreas >= MAX_AREAS) {
        printf("Cannot add more areas. Limit reached.\n");
        return;
    }

    if (findAreaIndex(g, name) != -1) {
        printf("Area '%s' already exists.\n", name);
        return;
    }

    strcpy(g->areaNames[g->numAreas], name);
    g->delivered[g->numAreas] = 0;

    for (int j = 0; j < MAX_AREAS; j++) {
        g->adj[g->numAreas][j] = 0;
        g->adj[j][g->numAreas] = 0;
    }

    g->numAreas++;
    printf("Area '%s' added.\n", name);
}

// ----------------------------
// Delete area
// ----------------------------
void deleteArea(Graph *g, char name[]) {
    int idx = findAreaIndex(g, name);

    if (idx == -1) {
        printf("Area '%s' not found.\n", name);
        return;
    }

    for (int i = idx; i < g->numAreas - 1; i++) {
        strcpy(g->areaNames[i], g->areaNames[i + 1]);
        g->delivered[i] = g->delivered[i + 1];

        for (int j = 0; j < g->numAreas; j++)
            g->adj[i][j] = g->adj[i + 1][j];
    }

    for (int j = idx; j < g->numAreas; j++)
        g->adj[j][idx] = g->adj[j][idx + 1];

    g->numAreas--;

    printf("Area '%s' deleted.\n", name);
}

// ----------------------------
// Add connection between areas
// ----------------------------
void addConnection(Graph *g, char src[], char dest[]) {
    int i = findAreaIndex(g, src);
    int j = findAreaIndex(g, dest);

    if (i == -1 || j == -1) {
        printf("One or both areas do not exist.\n");
        return;
    }

    g->adj[i][j] = 1;
    g->adj[j][i] = 1;

    printf("Connected '%s' <--> '%s'\n", src, dest);
}

// ----------------------------
// Display Graph
// ----------------------------
void displayGraph(Graph *g) {
    if (g->numAreas == 0) {
        printf("Graph is empty.\n");
        return;
    }

    printf("\nAREAS IN GRAPH:\n");
    for (int i = 0; i < g->numAreas; i++) {
        printf("%d. %s [%s]\n", i + 1, g->areaNames[i],
               g->delivered[i] ? "Delivered" : "Pending");
    }

    printf("\nCONNECTIONS (Adjacency Matrix):\n    ");
    for (int i = 0; i < g->numAreas; i++)
        printf("%-3d", i + 1);
    printf("\n");

    for (int i = 0; i < g->numAreas; i++) {
        printf("%-3d", i + 1);
        for (int j = 0; j < g->numAreas; j++)
            printf("%-3d", g->adj[i][j]);
        printf("\n");
    }
}

// ----------------------------
// Mark Delivered
// ----------------------------
void markDelivered(Graph *g, char name[]) {
    int idx = findAreaIndex(g, name);

    if (idx == -1) {
        printf("Area '%s' not found.\n", name);
        return;
    }

    g->delivered[idx] = 1;
    printf("Area '%s' marked as delivered.\n", name);
}

// ----------------------------
// BFS Traversal
// ----------------------------
void bfs(Graph *g, char start[]) {
    int startIndex = findAreaIndex(g, start);

    if (startIndex == -1) {
        printf("Area '%s' not found.\n", start);
        return;
    }

    int visited[MAX_AREAS] = {0};
    int queue[MAX_AREAS], front = 0, rear = 0;

    queue[rear++] = startIndex;
    visited[startIndex] = 1;

    printf("\nBFS Traversal: ");

    while (front < rear) {
        int curr = queue[front++];
        printf("%s ", g->areaNames[curr]);

        for (int i = 0; i < g->numAreas; i++) {
            if (g->adj[curr][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

// ----------------------------
// Dispatch Packages to Area
// ----------------------------
void dispatchPackages(Graph *g, Queue *q, char area[], int count) {
    int idx = findAreaIndex(g, area);

    if (idx == -1) {
        printf("Area '%s' not found.\n", area);
        return;
    }

    if (isEmpty(q)) {
        printf("No packages available.\n");
        return;
    }

    printf("\nDispatching %d packages to %s...\n", count, area);

    for (int i = 0; i < count; i++) {
        if (isEmpty(q)) {
            printf("Ran out of packages! Only %d were sent.\n", i);
            break;
        }
        dequeue(q, 1);
    }

    g->delivered[idx] = 1;
    printf("Area '%s' marked as delivered.\n", area);
}
