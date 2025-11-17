#include <stdio.h>
#include <string.h>
#include "flood.h"

// ---------------- BASIC GRAPH FUNCTIONS ----------------

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

    // Shift rows
    for (int i = idx; i < g->numAreas - 1; i++)
        for (int j = 0; j < g->numAreas; j++)
            g->adj[i][j] = g->adj[i + 1][j];

    // Shift columns
    for (int j = idx; j < g->numAreas - 1; j++)
        for (int i = 0; i < g->numAreas; i++)
            g->adj[i][j] = g->adj[i][j + 1];

    // Shift names + delivered flags
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

    // Header (1-based index) aligned with area numbers
    printf("      "); // 6 spaces before the header numbers
    for (int i = 0; i < g->numAreas; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < g->numAreas; i++) {

        // Row label (1-based) aligned with area numbering
        printf("%d  |  ", i + 1);

        for (int j = 0; j < g->numAreas; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}


// ---------------- DELIVERED FLAG ----------------

void markDelivered(Graph *g, char name[]) {
    int idx = findAreaIndex(g, name);
    if (idx == -1) {
        printf("Area not found.\n");
        return;
    }
    g->delivered[idx] = 1;
    printf("Area '%s' marked as delivered.\n", name);
}

// ---------------- BFS (SEARCH) ----------------

void bfs(Graph *g, char searchName[]) {
    int target = findAreaIndex(g, searchName);
    if (target == -1) {
        printf("Area '%s' not found in graph.\n", searchName);
        return;
    }

    int visited[MAX_AREAS] = {0};
    int queue[MAX_AREAS], front = 0, rear = 0;
    int found = 0;

    queue[rear++] = 0;  // Start from first area (index 0)
    visited[0] = 1;

    printf("\nSearching for area '%s' using BFS...\n", searchName);

    while (front < rear) {
        int u = queue[front++];
        printf("Visiting: %s\n", g->areaNames[u]);

        if (u == target) {
            found = 1;
            printf("\n Area '%s' FOUND! [Status: %s]\n", 
                   searchName, g->delivered[u] ? "Delivered" : "Pending");
            break;
        }

        for (int v = 0; v < g->numAreas; v++) {
            if (!visited[v] && g->adj[u][v] == 1) {
                queue[rear++] = v;
                visited[v] = 1;
            }
        }
    }

    if (!found) {
        printf("\n✗ Area '%s' not found (unreachable from area 0).\n", searchName);
    }
}

// ---------------- DISPATCH ----------------

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
