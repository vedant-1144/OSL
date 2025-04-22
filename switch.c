#include <stdio.h>

struct Process {
    int pid, arrival, burst, priority, ct, tat, wt, remaining;
};

void printTable(struct Process p[], int n) {
    printf("\n+-----+------------+----------+------------+--------------+----------+\n");
    printf("| PID | Arrival    | Burst    | Completion | Turnaround   | Waiting  |\n");
    printf("+-----+------------+----------+------------+--------------+----------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %d   | %d          | %d        | %d          | %d          | %d       |\n", 
               p[i].pid, p[i].arrival, p[i].burst, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("+-----+------------+----------+------------+--------------+----------+\n");
}

void fcfs(struct Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        time = (time > p[i].arrival ? time : p[i].arrival) + p[i].burst;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].arrival;
        p[i].wt = p[i].tat - p[i].burst;
    }
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
        if (idx == -1) time++;
        else {
            time += p[idx].burst;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].arrival;
            p[idx].wt = p[idx].tat - p[idx].burst;
            completed++;
        }
    }
    printTable(p, n);
}

void priorityScheduling(struct Process p[], int n) {
    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, min_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].ct == 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            time += p[idx].burst;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].arrival;
            p[idx].wt = p[idx].tat - p[idx].burst;
            completed++;
        }
    }
    printTable(p, n);
}

void roundRobin(struct Process p[], int n, int tq) {
    int time = 0, completed = 0;
    printf("\nGantt Chart:\n");
    printf("|");
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                int execTime = (p[i].remaining < tq) ? p[i].remaining : tq;
                printf(" P%d (%d-%d) |", p[i].pid, time, time + execTime);
                time += execTime;
                p[i].remaining -= execTime;
                if (p[i].remaining == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].arrival;
                    p[i].wt = p[i].tat - p[i].burst;
                    completed++;
                }
            }
        }
    }
    printf("\n");
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
        printf("Select Scheduling Algorithm:\n1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\nChoice: ");
        scanf("%d", &choice);
        if (choice == 3) {
            for (int i = 0; i < n; i++) {
                printf("Enter Priority for P%d: ", p[i].pid);
                scanf("%d", &p[i].priority);
            }
        }
        if (choice == 4) {
            printf("Enter Time Quantum: ");
            scanf("%d", &tq);
        }
        switch (choice) {
            case 1: fcfs(p, n); break;
            case 2: sjf(p, n); break;
            case 3: priorityScheduling(p, n); break;
            case 4: roundRobin(p, n, tq); break;
            default: printf("Invalid choice!\n"); break;
        }
    }
    return 0;
}