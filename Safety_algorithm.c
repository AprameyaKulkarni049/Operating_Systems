#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int n, m;
    int allocation[MAX_P][MAX_R], request[MAX_P][MAX_R];
    int available[MAX_R], work[MAX_R];
    bool finish[MAX_P] = {false};

    // 1. Input Section
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i]; // Work = Available
    }

    // 2. Detection Algorithm Logic
    bool progress;
    do {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_be_allocated = true;
                // Check if current process requests can be satisfied
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        can_be_allocated = false;
                        break;
                    }
                }

                if (can_be_allocated) {
                    // Process can finish, reclaim its allocated resources
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    } while (progress);

    // 3. Output Results
    bool deadlock = false;
    printf("\nDeadlocked processes: ");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (!deadlock)
        printf("None. System is in a safe state.");
    
    printf("\n");
    return 0;
}
