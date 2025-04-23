#include <stdio.h>
#include <stdbool.h>

#define RES 3

struct Process {
    int alloc[RES];
    int max[RES];
    int need[RES];
};

void banker(struct Process p[], int avail[], int n, int m) {
    bool finish[n];
    int rem[m], safeSeq[n];
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    for (int i = 0; i < m; i++) {
        rem[i] = avail[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];
        }
    }

    while (cnt < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {

            if ( !finish[i] ) {
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
            printf("System is in Unsafe State !!!");
            return;
        }
    }

    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d -> ", safeSeq[i]);
    }
    printf("\n");
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

    banker(p, avail, n, RES);

    return 0;
}