#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flood.h"

// Read a line safely
void readLine(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline
}

// Get integer safely
int getIntInput(const char *prompt) {
    char buf[20];
    int val;
    printf("%s", prompt);
    fgets(buf, sizeof(buf), stdin);
    val = atoi(buf);
    return val;
}

// Ask user to continue (robust version)
int askContinue(const char *msg) {
    char choice[5];
    while (1) {
        printf("%s (y/n): ", msg);
        readLine(choice, sizeof(choice));

        if (choice[0] == 'y' || choice[0] == 'Y')
            return 1;
        else if (choice[0] == 'n' || choice[0] == 'N')
            return 0;
        else
            printf("Invalid input. Please enter 'y' or 'n'.\n");
    }
}

// Display queue as total stock count only
// Display total stock count only (summary view)
void showStock(Queue *q) {
    if (isEmpty(q))
        printf("Inventory empty.\n");
    else
        printf("Current stock: %d packages.\n", q->rear - q->front + 1);
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
            //ADD STOCK
            case 1:
                if (isFull(&q)) {
                    printf("Inventory is already full! Cannot add more packages.\n");
                    break;
                }

                do {
                    num = getIntInput("Enter number of packages to add: ");

                    for (int i = 0; i < num; i++) {
                        if (isFull(&q)) {
                            printf("Inventory full! Added %d packages so far.\n", i);
                            break;
                        }
                        enqueue(&q, 1);
                    }

                    displayQueue(&q);

                    if (isFull(&q)) {
                        printf("Inventory now full — returning to main menu.\n");
                        break;
                    }
                } while (askContinue("Add more packages?"));
                break;

            //REMOVE STOCK
            case 2:
                if (isEmpty(&q)) {
                    printf("No packages available for transport.\n");
                    break;
                }

                do {
                    num = getIntInput("Enter number of packages to transport: ");
                    dequeue(&q, num);
                    displayQueue(&q);

                    if (isEmpty(&q)) {
                        printf("All packages transported. Inventory empty.\n");
                        break;
                    }
                } while (askContinue("Remove more packages?"));
                break;

            //ADD AREA
            case 3:
                do {
                    printf("Enter area name: ");
                    readLine(area, sizeof(area));
                    addArea(&g, area);
                } while (askContinue("Add another area?"));
                break;

            //DELETE AREA
            case 4:
                do {
                    printf("Enter area name to delete: ");
                    readLine(area, sizeof(area));
                    deleteArea(&g, area);
                } while (askContinue("Delete another area?"));
                break;

            //ADD CONNECTION
            case 5:
                do {
                    printf("Enter source area: ");
                    readLine(src, sizeof(src));
                    printf("Enter destination area: ");
                    readLine(dest, sizeof(dest));
                    addConnection(&g, src, dest);
                } while (askContinue("Add another connection?"));
                break;

            //DISPLAY GRAPH
            case 6:
                displayGraph(&g);
                break;

            //MARK DELIVERED
            case 7:
                do {
                    printf("Enter area name to mark delivered: ");
                    readLine(area, sizeof(area));
                    markDelivered(&g, area);
                } while (askContinue("Mark another area as delivered?"));
                break;

            //DISPLAY STOCK SUMMARY
            case 8:
                displayQueue(&q);
                break;

            //EXIT
            case 0:
                printf("Exiting system. Stay safe!\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a number from 0 to 8.\n");
        }
    }
}
