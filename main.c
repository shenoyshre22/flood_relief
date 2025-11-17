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

// Display total stock only
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
        printf("\nFLOOD RELIEF MANAGEMENT\n");
        printf("1. Add stock to inventory\n");
        printf("2. Remove stock for transport\n");
        printf("3. Add area\n");
        printf("4. Delete area\n");
        printf("5. Add connectivity\n");
        printf("6. Display graph\n");
        printf("7. Mark area as delivered\n");
        printf("8. Display stock\n");
        printf("9. BFS Traversal\n");               // ★ ADDED
        printf("10. Dispatch Packages to Area\n");  // ★ ADDED
        printf("0. Exit\n");

        choice = getIntInput("Enter choice: ");

        switch (choice) {

            // --- existing cases unchanged ---

            case 9: {
                char start[50];
                printf("Enter starting area name for BFS: ");
                readLine(start, sizeof(start));
                bfs(&g, start);
                break;
            }

            case 10: {
                char area[50];
                int count;

                printf("Enter area to dispatch packages to: ");
                readLine(area, sizeof(area));

                printf("Enter number of packages to send: ");
                scanf("%d", &count);
                getchar(); // clear newline

                dispatchPackages(&g, &q, area, count);   // ★ FIXED q
                break;
            }

            case 0:
                printf("Exiting system. Stay safe!\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a number from 0 to 10.\n"); // ★ FIXED
        }
    }
}
