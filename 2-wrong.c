#include <stdio.h>

struct Process {
    int pid, arrival, burst, priority, ct, tat, wt, remaining;
};

void calculateMetrics(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].arrival;
        p[i].wt = p[i].tat - p[i].burst;
    }
}

void printTable(struct Process p[], int n) {
    printf("\n+-----+------------+----------+------------+--------------+----------+\n");
    printf("| PID | Arrival    | Burst    | Completion | Turnaround   | Waiting  |\n");
    printf("+-----+------------+----------+------------+--------------+----------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %2d  | %8d  | %6d   | %10d  | %10d    | %6d   |\n", 
               p[i].pid, p[i].arrival, p[i].burst, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("+-----+------------+----------+------------+--------------+----------+\n");
}

void printGantt(int pid, int start, int end) {
    printf("| P%d (%d-%d) ", pid, start, end);
}

void fcfs(struct Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival) time = p[i].arrival;
        time += p[i].burst;
        p[i].ct = time;
    }
    calculateMetrics(p, n);
    printTable(p, n);
}

void sjf(struct Process p[], int n) {
    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, min_burst = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].ct == 0 && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
        } else {
            time += p[idx].burst;
            p[idx].ct = time;
            completed++;
        }
    }
    calculateMetrics(p, n);
    printTable(p, n);
}

void sjfPreemptive(struct Process p[], int n) {
    int time = 0, completed = 0;
    printf("\nGantt Chart:\n|");
    while (completed < n) {
        int idx = -1, min_burst = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min_burst) {
                min_burst = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
        } else {
            printGantt(p[idx].pid, time, time + 1);
            time++;
            p[idx].remaining--;
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            }
        }
    }
    printf("|\n");
    calculateMetrics(p, n);
    printTable(p, n);
}

void priority(struct Process p[], int n) {
    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, min_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].ct == 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
        } else {
            time += p[idx].burst;
            p[idx].ct = time;
            completed++;
        }
    }
    calculateMetrics(p, n);
    printTable(p, n);
}

void priorityPreemptive(struct Process p[], int n) {
    int time = 0, completed = 0;
    printf("\nGantt Chart:\n|");
    while (completed < n) {
        int idx = -1, min_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
        } else {
            printGantt(p[idx].pid, time, time + 1);
            time++;
            p[idx].remaining--;
            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            }
        }
    }
    printf("|\n");
    calculateMetrics(p, n);
    printTable(p, n);
}

void roundRobin(struct Process p[], int n, int tq) {
    int time = 0, completed = 0;
    printf("\nGantt Chart:\n|");
    while (completed < n) {
        int progress = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                int execTime = (p[i].remaining < tq) ? p[i].remaining : tq;
                printGantt(p[i].pid, time, time + execTime);
                time += execTime;
                p[i].remaining -= execTime;
                if (p[i].remaining == 0) {
                    p[i].ct = time;
                    completed++;
                }
                progress = 1;
            }
        }
        if (!progress) time++;
    }
    printf("|\n");
    calculateMetrics(p, n);
    printTable(p, n);
}

int main() {
    int choice, tq;
    while (1) {
        int n;
        printf("Enter number of processes (Enter 0 to exit): ");
        scanf("%d", &n);
        if (n == 0) break;

        struct Process p[n];
        for (int i = 0; i < n; i++) {
            p[i].pid = i + 1;
            printf("Enter Arrival and Burst Time for P%d: ", p[i].pid);
            scanf("%d %d", &p[i].arrival, &p[i].burst);
            p[i].remaining = p[i].burst;
        }

        printf("Select Scheduling Algorithm:\n");
        printf("1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n4. Priority (Non-Preemptive)\n5. Priority (Preemptive)\n6. Round Robin\nChoice: ");
        scanf("%d", &choice);

        if (choice == 4 || choice == 5) {
            for (int i = 0; i < n; i++) {
                printf("Enter Priority for P%d: ", p[i].pid);
                scanf("%d", &p[i].priority);
            }
        }
        if (choice == 6) {
            printf("Enter Time Quantum: ");
            scanf("%d", &tq);
        }

        switch (choice) {
            case 1: fcfs(p, n); break;
            case 2: sjf(p, n); break;
            case 3: sjfPreemptive(p, n); break;
            case 4: priority(p, n); break;
            case 5: priorityPreemptive(p, n); break;
            case 6: roundRobin(p, n, tq); break;
            default: printf("Invalid choice!\n"); break;
        }
    }
    return 0;
}
