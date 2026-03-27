void preemptiveSRTF(process p[], int n) {
    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;
        int minRT = 9999;

        // Select process with shortest remaining time among arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].finished == 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            currentTime++;

            if (p[idx].rt == 0) {
                p[idx].finished = 1;
                p[idx].ct = currentTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    printf("\n--- Preemptive SRTF ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nArrival time of P%d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Burst time of P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].finished = 0;
    }

    printf("\nEnter choice:\n1. Non-Preemptive SJF\n2. Preemptive SRTF\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            nonPreemptiveSJF(p, n);
            break;
        case 2:
            preemptiveSRTF(p, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
