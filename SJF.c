#include <stdio.h>

typedef struct {
    int pid, at, bt, ct, rt, wt, tat, finished;
} process;

void nonPreemptiveSJF(process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = 9999;

        // Select process with shortest burst time among arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].finished == 0 && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            // If CPU is idle until this process arrives
            if (currentTime < p[idx].at) {
                currentTime = p[idx].at;
            }

            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].finished = 1;
            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
            completed++;
        } else {
            currentTime++;
        }
    }

    printf("\n--- Non-Preemptive SJF ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}
