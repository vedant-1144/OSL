#include <stdio.h>
#include <stdbool.h>

void printTable(int pSize[], int alloc[], int ogbSize[], int n, int m) {
    printf("\n%-10s%-15s%-15s%-15s%-15s\n", 
           "Process", "PSize", "Block", "BSize", "Remaining");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (alloc[i] == -1) {
            printf("%-10d%-15d%-15s%-15s%-15s\n", 
                   i, pSize[i], "N/A", "N/A", "N/A");
        } else {
            int block = alloc[i];
            int rem = ogbSize[block] - pSize[i];
            printf("%-10d%-15d%-15d%-15d%-15d\n", 
                   i+1, pSize[i], block+1, ogbSize[block], rem);
            ogbSize[block] = rem;
        }
    }
}

void firstFit(int bSize[], int m, int pSize[], int n) {
    int alloc[n];
    int ogbSize[m];
    for (int i = 0; i < m; i++) ogbSize[i] = bSize[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (bSize[j] >= pSize[i]) {
                alloc[i] = j;
                bSize[j] -= pSize[i];
                break;
            }
        }
    }
    printTable(pSize, alloc, ogbSize, n, m);
}

void bestFit(int bSize[], int m, int pSize[], int n) {
    int alloc[n];
    int ogbSize[m];
    for (int i = 0; i < m; i++) ogbSize[i] = bSize[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1, mini = 1e9;
        for (int j = 0; j < m; j++) {
            if (bSize[j] >= pSize[i] && bSize[j] < mini) {
                bestIdx = j;
                mini = bSize[j];
            }
        }
        if (bestIdx != -1) {
            alloc[i] = bestIdx;
            bSize[bestIdx] -= pSize[i];
        }
    }

    printTable(pSize, alloc, ogbSize, n, m);
}

void worstFit(int bSize[], int m, int pSize[], int n) {
    int alloc[n];
    int ogbSize[m];
    for (int i = 0; i < m; i++) ogbSize[i] = bSize[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1, maxi = -1e9;
        for (int j = 0; j < m; j++) {
            if (bSize[j] >= pSize[i] && bSize[j] > maxi) {
                worstIdx = j;
                maxi = bSize[j];
            }
        }
        if (worstIdx != -1) {
            alloc[i] = worstIdx;
            bSize[worstIdx] -= pSize[i];
        }
    }

    printTable(pSize, alloc, ogbSize, n, m);
}

void nextFit(int bSize[], int m, int pSize[], int n) {
    int alloc[n];
    int ogbSize[m];
    for (int i = 0; i < m; i++) ogbSize[i] = bSize[i];
    for (int i = 0; i < n; i++) alloc[i] = -1;
    int last = 0;

    for (int i = 0; i < n; i++) {
        int j = last;
        while (true) {
            if (bSize[j] >= pSize[i]) {
                alloc[i] = j;
                bSize[j] -= pSize[i];
                last = j;
                break;
            }
            j = (j + 1) % m;
            if (j == last) break; // No more blocks available
        }
    }
    
    printTable(pSize, alloc, ogbSize, n, m);
}

int main() {
    int m, n;
    printf("Enter Number of Memory Blocks: ");
    scanf("%d", &m);
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    int bSize[m], pSize[n], allocate[m];

    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &bSize[i]);
    }

    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &pSize[i]);
    }

    while (true) {
        int choice;
        printf("Choose Your Memmory Allocation Technique :- \n");
        printf("1.First Fit  2.Best Fit  3.Worst Fit  4.Next Fit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            for (int i = 0; i < m; i++)
                allocate[i] = bSize[i];
            firstFit(allocate, m, pSize, n);
            break;

        case 2:
            for (int i = 0; i < m; i++)
                allocate[i] = bSize[i];
            bestFit(allocate, m, pSize, n);
            break;

        case 3:
            for (int i = 0; i < m; i++)
                allocate[i] = bSize[i];
            worstFit(allocate, m, pSize, n);
            break;

        case 4:
            for (int i = 0; i < m; i++)
                allocate[i] = bSize[i];
            nextFit(allocate, m, pSize, n);
            break;

        default:
            printf("Invalid Choice !!! \n");
            return 0;
        }
    }

    return 0;
}