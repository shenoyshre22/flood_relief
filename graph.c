#include <stdio.h>
#include <string.h>
#include "flood.h"

void initGraph(Graph *g) {
    g->numAreas = 0;
    for (int i = 0; i < MAX_AREAS; i++) {
        for (int j = 0; j < MAX_AREAS; j++)
            g->adj[i][j] = 0;
        g->delivered[i] = 0;
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
        printf("Cannot add more areas.\n");
        return;
    }

    size_t cap = sizeof g->areaNames[g->numAreas]; // capacity for one name
    char tmp[sizeof g->areaNames[0]];
    // Copy safely and ensure null-termination
    strncpy(tmp, name, cap - 1);
    tmp[cap - 1] = '\0';

    // Trim trailing newline/carriage return if caller used fgets
    size_t len = strlen(tmp);
    while (len > 0 && (tmp[len - 1] == '\n' || tmp[len - 1] == '\r')) {
        tmp[--len] = '\0';
    }

    if (len == 0) {
        printf("Name cannot be empty.\n");
        return;
    }

    if (findAreaIndex(g, tmp) != -1) {
        printf("Area already exists.\n");
        return;
    }

    // Copy into graph storage
    strncpy(g->areaNames[g->numAreas], tmp, cap - 1);
    g->areaNames[g->numAreas][cap - 1] = '\0';

    g->numAreas++;
    printf("Area '%s' added successfully.\n", tmp);
}

void deleteArea(Graph *g, char name[]) {
    int index = findAreaIndex(g, name);
    if (index == -1) {
        printf("Area not found.\n");
        return;
    }

    // Shift rows and columns
    for (int i = index; i < g->numAreas - 1; i++) {
        strcpy(g->areaNames[i], g->areaNames[i + 1]);
        g->delivered[i] = g->delivered[i + 1];
        for (int j = 0; j < g->numAreas; j++)
            g->adj[i][j] = g->adj[i + 1][j];
    }
    for (int j = index; j < g->numAreas - 1; j++) {
        for (int i = 0; i < g->numAreas; i++)
            g->adj[i][j] = g->adj[i][j + 1];
    }

    g->numAreas--;
    printf("Area '%s' deleted successfully.\n", name);
}

void addConnection(Graph *g, char src[], char dest[]) {
    int s = findAreaIndex(g, src);
    int d = findAreaIndex(g, dest);

    if (s == -1 || d == -1) {
        printf("Both areas must exist before connecting.\n");
        return;
    }
    g->adj[s][d] = g->adj[d][s] = 1;
    printf("Connection added between '%s' and '%s'.\n", src, dest);
}

void displayGraph(Graph *g) {
    printf("\n--- Areas and Connections ---\n");
    for (int i = 0; i < g->numAreas; i++) {
        printf("%s [%s] --> ", g->areaNames[i],
               g->delivered[i] ? "Delivered" : "Pending");
        for (int j = 0; j < g->numAreas; j++) {
            if (g->adj[i][j])
                printf("%s ", g->areaNames[j]);
        }
        printf("\n");
    }
}

void markDelivered(Graph *g, char name[]) {
    int index = findAreaIndex(g, name);
    if (index == -1) {
        printf("Area not found.\n");
        return;
    }
    g->delivered[index] = 1;
    printf("Marked '%s' as delivered.\n", name);
}
