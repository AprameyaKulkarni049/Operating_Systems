#include <stdio.h>
#include <math.h>
#define MAX 10
#define SIM_TIME 150

typedef struct {
    int id;
    int exec_time;
    int period;
    int deadline;
    int remaining_time;
    int next_release;
    int weight;
} Task;

int n;
Task tasks[MAX];

void rateMonotonic() {
    printf("\n--- Rate Monotonic Scheduling ---\n");

    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = 0;
        tasks[i].next_release = 0;
    }

    for (int t = 0; t < SIM_TIME; t++) {

        // Release tasks
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_release) {
                tasks[i].remaining_time = tasks[i].exec_time;
                tasks[i].next_release += tasks[i].period;
            }
        }

        // Pick task with smallest period (highest priority)
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                if (selected == -1 || tasks[i].period < tasks[selected].period)
                    selected = i;
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", t, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        tasks[i].id = i + 1;

        printf("Execution time: ");
        scanf("%d", &tasks[i].exec_time);

        printf("Period: ");
        scanf("%d", &tasks[i].period);
rateMonotonic();
   return 0;
}
