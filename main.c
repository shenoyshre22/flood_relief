#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flood.h"

//read full line
void readLine(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

//int input
int getIntInput(const char *prompt) {
    char buf[50];
    int val;

    while (1) {
        printf("%s", prompt);
        fgets(buf, sizeof(buf), stdin);

        if (sscanf(buf, "%d", &val) == 1)
            return val;

        printf("Invalid number. Try again.\n");
    }
}

//ask y or n
int askContinue(const char *msg) {
    char line[10];

    while (1) {
        printf("%s (y/n): ", msg);
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) continue;

        if (line[0] == 'y' || line[0] == 'Y') return 1;
        if (line[0] == 'n' || line[0] == 'N') return 0;

        printf("Invalid input.\n");
    }
}

int main() {
    Queue q;
    Graph g;
    initQueue(&q);
    initGraph(&g);

    int choice, num;
    char area[50], src[50], dest[50];

    while (1) {
        printf("\nFLOOD RELIEF MANAGEMENT\n");
        printf("1. Add stock to inventory\n");
        printf("2. Remove stock for transport\n");
        printf("3. Add area\n");
        printf("4. Delete area\n");
        printf("5. Add connectivity\n");
        printf("6. Display graph\n");
        printf("7. Mark area as delivered\n");
        printf("8. Display stock\n");
        printf("9. Dispatch packages to area\n");
        printf("10.BFS traversal to find shortest path\n");
        printf("0. Exit\n");

        choice = getIntInput("Enter choice: ");

        switch (choice) {

        //add stock to queue
        case 1:
            if (isFull(&q)) {
                printf("Inventory full!\n");
                break;
            }
            do {
                num = getIntInput("How many packages to add? ");

                for (int i = 0; i < num; i++) {
                    if (isFull(&q)) {
                        printf("Inventory full! Added %d so far.\n", i);
                        break;
                    }
                    enqueue(&q, 1);
                }

                displayQueue(&q);

                if (isFull(&q)) break;

            } while (askContinue("Add more packages?"));
            break;

        //remove stock from queue
        case 2:
            if (isEmpty(&q)) {
                printf("Inventory empty.\n");
                break;
            }
            do {
                num = getIntInput("How many packages to transport? ");
                dequeue(&q, num);
                displayQueue(&q);

                if (isEmpty(&q)) {
                    printf("All packages transported.\n");
                    break;
                }

            } while (askContinue("Remove more packages?"));
            break;

        //add area to graph
        case 3:
            do {
                printf("Enter area name: ");
                readLine(area, sizeof(area));
                addArea(&g, area);
            } while (askContinue("Add another area?"));
            break;

        //delete area from graph
        case 4:
            do {
                printf("Enter area name to delete: ");
                readLine(area, sizeof(area));
                deleteArea(&g, area);
            } while (askContinue("Delete another area?"));
            break;

        //connections
        case 5:
            do {
                printf("Enter source area: ");
                readLine(src, sizeof(src));
                printf("Enter destination area: ");
                readLine(dest, sizeof(dest));

                addConnection(&g, src, dest);

            } while (askContinue("Add another connection?"));
            break;

        //display graph
        case 6:
            displayGraph(&g);
            break;

        //marking as delivered
        case 7:
            do {
                printf("Enter area name: ");
                readLine(area, sizeof(area));
                markDelivered(&g, area);
            } while (askContinue("Mark another delivered?"));
            break;

        //display inventory stock
        case 8:
            displayQueue(&q);
            break;

        //area wise dispatch of packages
        case 9:
            printf("Enter area to dispatch: ");
            readLine(area, sizeof(area));
            num = getIntInput("Enter number of packages: ");
            dispatchPackages(&g, &q, area, num);
            break;

        //bfs
        case 10:
            do {
                    printf("Enter source area: ");
                    readLine(src, sizeof(src));
                    printf("Enter destination area: ");
                    readLine(dest, sizeof(dest));
                    bfsShortestPath(&g, src, dest);
                } while (askContinue("Find another shortest path?"));
                break;

        //exit
        case 0:
            printf("Exiting system. Stay safe!\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }
}
