#include <stdio.h>
#include <stdbool.h>

#define RES 3

struct Process {
    int alloc[RES];
    int max[RES];
    int need[RES];
};

void calculateNeed(struct Process p[], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
        }
    }
}

bool isSafe(struct Process p[], int avail[], int n, int m, int safeSeq[]) {
    bool finish[n];
    int rem[m];
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    for (int i = 0; i < m; i++) {
        rem[i] = avail[i];
    }

    while (cnt < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAlloc = true;
                for (int j = 0; j < m; j++) {
                    if (p[i].need[j] > rem[j]) {
                        canAlloc = false;
                        break;
                    }
                }

                if (canAlloc) {
                    for (int j = 0; j < m; j++) {
                        rem[j] += p[i].alloc[j];
                    }
                    safeSeq[cnt++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }
    return true;
}

bool requestResources(struct Process p[], int avail[], int n, int m, int processID, int request[]) {
    for (int j = 0; j < m; j++) {
        if (request[j] > p[processID].need[j] || request[j] > avail[j]) {
            printf("Request exceeds maximum need or available resources.\n");
            return false;
        }
    }

    for (int j = 0; j < m; j++) {
        avail[j] -= request[j];
        p[processID].alloc[j] += request[j];
        p[processID].need[j] -= request[j];
    }

    int safeSeq[n];
    if (!isSafe(p, avail, n, m, safeSeq)) {
        for (int j = 0; j < m; j++) {
            avail[j] += request[j];
            p[processID].alloc[j] -= request[j];
            p[processID].need[j] += request[j];
        }
        printf("Request denied to prevent unsafe state.\n");
        return false;
    }

    printf("Request granted. Updated allocation successful.\n");
    return true;
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int avail[RES];

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < RES; j++) {
            scanf("%d", &p[i].alloc[j]);
        }
    }

    printf("Enter the MaxNeed matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < RES; j++) {
            scanf("%d", &p[i].max[j]);
        }
    }

    printf("Enter the Available resources: ");
    for (int i = 0; i < RES; i++) {
        scanf("%d", &avail[i]);
    }

    calculateNeed(p, n, RES);

    int safeSeq[n];
    if (isSafe(p, avail, n, RES, safeSeq)) {
        printf("Initial safe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d -> ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("System is initially in an unsafe state!\n");
    }

    int processID, request[RES];
    printf("Enter process ID requesting resources (or -1 to skip): ");
    scanf("%d", &processID);

    if (processID >= 0 && processID < n) {
        printf("Enter requested resources: ");
        for (int j = 0; j < RES; j++) {
            scanf("%d", &request[j]);
        }

        if (requestResources(p, avail, n, RES, processID, request)) {
            if (isSafe(p, avail, n, RES, safeSeq)) {
                printf("Updated safe sequence: ");
                for (int i = 0; i < n; i++) {
                    printf("P%d -> ", safeSeq[i]);
                }
                printf("\n");
            } else {
                printf("System in unsafe state after request.\n");
            }
        }
    }

    return 0;
}