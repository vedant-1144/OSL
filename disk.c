#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fifo(int requests[], int n, int head) {
    int total = 0;
    int curr = head;
    
    printf("\nFIFO Disk Scheduling :- \n");
    printf("Initial Head Position: %d\n", head);

    printf("Request Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");
    
    printf("Head Movement:\n");
    for (int i = 0; i < n; i++) {
        int distance = abs(requests[i] - curr);
        total += distance;
        
        printf("Move from %d -> %d (Distance: %d)\n", 
               curr, requests[i], distance);
        
        curr = requests[i];
    }
    
    printf("\nTotal Head Movement: %d\n", total);
    printf("Average Seek Length: %.2f\n\n", (float)total / n);
}

void sstf(int requests[], int n, int head) {
    int total = 0;
    int curr = head;
    int serviced[n];
    for (int i = 0; i < n; i++) serviced[i] = 0;
    
    printf("\nSSTF Disk Scheduling\n");
    printf("Initial Head Position: %d\n", head);
    printf("Request Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");
    
    printf("Head Movement:\n");
    for (int count = 0; count < n; count++) {
        int min_distance = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < n; i++) {
            if (!serviced[i]) {
                int distance = abs(requests[i] - curr);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = i;
                }
            }
        }
        
        if (min_index == -1) break;
        
        serviced[min_index] = 1;
        total += min_distance;
        
        printf("Move from %d -> %d (Distance: %d)\n", 
               curr, requests[min_index], min_distance);
        
        curr = requests[min_index];
    }
    
    printf("\nTotal Head Movement: %d\n", total);
    printf("Average Seek Length: %.2f\n\n", (float)total / n);
}

void scan(int requests[], int n, int head, int direction, int disk_size) {
    int total = 0;
    int curr = head;
    int serviced[n];
    for (int i = 0; i < n; i++) serviced[i] = 0;
    
    printf("\nSCAN (Elevator) Disk Scheduling\n");
    printf("Initial Head Position: %d\n", head);
    printf("Direction: %s\n", direction == 1 ? "Right (towards higher cylinders)" : "Left (towards lower cylinders)");
    printf("Request Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");
    
    printf("Head Movement:\n");
    
    // Sort requests for easier processing
    int sorted[n];
    for (int i = 0; i < n; i++) sorted[i] = requests[i];
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (sorted[j] > sorted[j+1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    
    if (direction == 1) { // Moving right (towards higher cylinders)
        // First move right
        for (int i = 0; i < n; i++) {
            if (sorted[i] >= curr) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
            }
        }

        // Move to end if not there
        if (curr != disk_size - 1) {
            int distance = abs((disk_size - 1) - curr);
            total += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   curr, disk_size - 1, distance);
            curr = disk_size - 1;
        }

        // Then move left
        for (int i = n-1; i >= 0; i--) {
            if (sorted[i] < head) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
            }
        }
    } else { // Moving left (towards lower cylinders)
        // First move left
        for (int i = n-1; i >= 0; i--) {
            if (sorted[i] <= curr) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
            }
        }

        // Move to beginning if not there
        if (curr != 0) {
            int distance = abs(0 - curr);
            total += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   curr, 0, distance);
            curr = 0;
        }

        // Then move right
        for (int i = 0; i < n; i++) {
            if (sorted[i] > head) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
            }
        }
    }
    
    printf("\nTotal Head Movement: %d\n", total);
    printf("Average Seek Length: %.2f\n\n", (float)total / n);
}

void cscan(int requests[], int n, int head, int direction, int disk_size) {
    int total = 0;
    int curr = head;
    int serviced[n];
    for (int i = 0; i < n; i++) serviced[i] = 0;
    
    printf("\nC-SCAN (Circular SCAN) Disk Scheduling\n");
    printf("Initial Head Position: %d\n", head);
    printf("Direction: %s\n", direction == 1 ? "Right (towards higher cylinders)" : "Left (towards lower cylinders)");
    printf("Request Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");
    
    printf("Head Movement:\n");
    
    // Sort requests for easier processing
    int sorted[n];
    for (int i = 0; i < n; i++) sorted[i] = requests[i];
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (sorted[j] > sorted[j+1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }
    
    if (direction == 1) {
        for (int i = 0; i < n; i++) {
            if (sorted[i] >= curr && !serviced[i]) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
                serviced[i] = 1;
            }
        }

        if (curr != disk_size - 1) {
            int distance = abs((disk_size - 1) - curr);
            total += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   curr, disk_size - 1, distance);
            curr = disk_size - 1;
        }
        printf("Jump from %d -> 0 (Distance: %d)\n", 
               disk_size - 1, disk_size - 1);
        total += disk_size - 1;
        curr = 0;

        for (int i = 0; i < n; i++) {
            if (!serviced[i]) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
                serviced[i] = 1;
            }
        }
    } else {

        for (int i = n-1; i >= 0; i--) {
            if (sorted[i] <= curr && !serviced[i]) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
                serviced[i] = 1;
            }
        }

        if (curr != 0) {
            int distance = abs(0 - curr);
            total += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   curr, 0, distance);
            curr = 0;
        }
        printf("Jump from 0 -> %d (Distance: %d)\n", 
               disk_size - 1, disk_size - 1);
        total += disk_size - 1;
        curr = disk_size - 1;

        for (int i = n-1; i >= 0; i--) {
            if (!serviced[i]) {
                int distance = abs(sorted[i] - curr);
                total += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       curr, sorted[i], distance);
                curr = sorted[i];
                serviced[i] = 1;
            }
        }
    }
    
    printf("\nTotal Head Movement: %d\n", total);
    printf("Average Seek Length: %.2f\n\n", (float)total / n);
}

int main() {
    int n, head, dir, disk_size;
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    
    int req[n];
    
    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    printf("Enter the disk size (max cylinder number): ");
    scanf("%d", &disk_size);
    
    int choice;
    while (1) {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. FIFO\n 2. SSTF\n 3. SCAN\n 4. C-SCAN\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                fifo(req, n, head);
                break;
            case 2:
                sstf(req, n, head);
                break;
            case 3:
                printf("Enter Dir -> 0.Left, 1.Right: ");
                scanf("%d", &dir);
                scan(req, n, head, dir, disk_size);
                break;
            case 4:
                printf("Enter Dir -> 0.Left, 1.Right : ");
                scanf("%d", &dir);
                cscan(req, n, head, dir, disk_size);
                break;
            default:
                printf("Invalid choice! Exiting Program...\n");
                return 0;
        }
    }

    return 0;
}