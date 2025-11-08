#include <stdio.h>
#include <string.h>
#include "flood.h"

// helper function to safely read a line with spaces
void readLine(char *str, int size) {
    // flush leftover input if needed
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline
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
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of packages to add: ");
                scanf("%d", &num);
                for (int i = 0; i < num; i++) {
                    if (isFull(&q)) {
                        printf("Inventory full! %d packages added so far.\n", i);
                        break;
                    }
                    enqueue(&q, 1);
                }
                break;

            case 2:
                printf("Enter number of packages to transport: ");
                scanf("%d", &num);
                dequeue(&q, num);
                break;

            case 3:
                printf("Enter area name: ");
                readLine(area, sizeof(area));
                addArea(&g, area);
                break;

            case 4:
                printf("Enter area name to delete: ");
                readLine(area, sizeof(area));
                deleteArea(&g, area);
                break;

            case 5:
                printf("Enter source area: ");
                readLine(src, sizeof(src));
                printf("Enter destination area: ");
                readLine(dest, sizeof(dest));
                addConnection(&g, src, dest);
                break;

            case 6:
                displayGraph(&g);
                break;

            case 7:
                printf("Enter area name to mark delivered: ");
                readLine(area, sizeof(area));
                markDelivered(&g, area);
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
