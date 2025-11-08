#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flood.h"

// helper function to safely read line input
void readLine(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline
}

// helper to get integer input safely
int getIntInput(const char *prompt) {
    char buf[20];
    int val;
    printf("%s", prompt);
    fgets(buf, sizeof(buf), stdin);
    val = atoi(buf);
    return val;
}

// ask user if they want to continue an operation
int askContinue(const char *msg) {
    char choice[5];
    printf("%s (y/n): ", msg);
    readLine(choice, sizeof(choice));
    return (choice[0] == 'y' || choice[0] == 'Y');
}

int main() {
    Queue q;
    Graph g;
    initQueue(&q);
    initGraph(&g);

    int choice, num;
    char area[50], src[50], dest[50];

    while (1) {
        printf("\n==== FLOOD RELIEF MANAGEMENT ====\n");
        printf("1. Add stock to inventory\n");
        printf("2. Remove stock for transport\n");
        printf("3. Add area\n");
        printf("4. Delete area\n");
        printf("5. Add connectivity\n");
        printf("6. Display graph\n");
        printf("7. Mark area as delivered\n");
        printf("8. Display stock\n");
        printf("0. Exit\n");

        choice = getIntInput("Enter choice: ");

        switch (choice) {
            case 1:
                do {
                    num = getIntInput("Enter number of packages to add: ");
                    for (int i = 0; i < num; i++) {
                        if (isFull(&q)) {
                            printf("Inventory full! %d packages added so far.\n", i);
                            break;
                        }
                        enqueue(&q, 1);
                    }
                    displayQueue(&q);
                } while (askContinue("Add more packages?"));
                break;

            case 2:
                do {
                    num = getIntInput("Enter number of packages to transport: ");
                    dequeue(&q, num);
                    displayQueue(&q);
                } while (askContinue("Remove more packages?"));
                break;

            case 3:
                do {
                    printf("Enter area name: ");
                    readLine(area, sizeof(area));
                    addArea(&g, area);
                } while (askContinue("Add another area?"));
                break;

            case 4:
                do {
                    printf("Enter area name to delete: ");
                    readLine(area, sizeof(area));
                    deleteArea(&g, area);
                } while (askContinue("Delete another area?"));
                break;

            case 5:
                do {
                    printf("Enter source area: ");
                    readLine(src, sizeof(src));
                    printf("Enter destination area: ");
                    readLine(dest, sizeof(dest));
                    addConnection(&g, src, dest);
                } while (askContinue("Add another connection?"));
                break;

            case 6:
                displayGraph(&g);
                break;

            case 7:
                do {
                    printf("Enter area name to mark delivered: ");
                    readLine(area, sizeof(area));
                    markDelivered(&g, area);
                } while (askContinue("Mark another area as delivered?"));
                break;

            case 8:
                displayQueue(&q);
                break;

            case 0:
                printf("Exiting system. Stay safe!\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}