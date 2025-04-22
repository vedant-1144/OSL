#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fifo(int requests[], int n, int head) {
    int total_movement = 0;
    int current_position = head;
    
    printf("\nFIFO Disk Scheduling :- \n");
    printf("Initial Head Position: %d\n", head);

    printf("Request Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n\n");
    
    printf("Head Movement:\n");
    for (int i = 0; i < n; i++) {
        int distance = abs(requests[i] - current_position);
        total_movement += distance;
        
        printf("Move from %d -> %d (Distance: %d)\n", 
               current_position, requests[i], distance);
        
        current_position = requests[i];
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Seek Length: %.2f\n\n", (float)total_movement / n);
}

void sstf(int requests[], int n, int head) {
    int total_movement = 0;
    int current_position = head;
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
                int distance = abs(requests[i] - current_position);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = i;
                }
            }
        }
        
        if (min_index == -1) break;
        
        serviced[min_index] = 1;
        total_movement += min_distance;
        
        printf("Move from %d -> %d (Distance: %d)\n", 
               current_position, requests[min_index], min_distance);
        
        current_position = requests[min_index];
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Seek Length: %.2f\n\n", (float)total_movement / n);
}

void scan(int requests[], int n, int head, int direction, int disk_size) {
    int total_movement = 0;
    int current_position = head;
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

        for (int i = 0; i < n; i++) {
            if (sorted[i] >= current_position && !serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }

        if (current_position != disk_size - 1) {
            int distance = abs((disk_size - 1) - current_position);
            total_movement += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   current_position, disk_size - 1, distance);
            current_position = disk_size - 1;
        }

        for (int i = n-1; i >= 0; i--) {
            if (!serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }
	}

        for (int i = n-1; i >= 0; i--) {
            if (sorted[i] <= current_position && !serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }

        if (current_position != 0) {
            int distance = abs(0 - current_position);
            total_movement += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   current_position, 0, distance);
            current_position = 0;
        }

        for (int i = 0; i < n; i++) {
            if (!serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Seek Length: %.2f\n\n", (float)total_movement / n);
}

void cscan(int requests[], int n, int head, int direction, int disk_size) {
    int total_movement = 0;
    int current_position = head;
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
            if (sorted[i] >= current_position && !serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }

        if (current_position != disk_size - 1) {
            int distance = abs((disk_size - 1) - current_position);
            total_movement += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   current_position, disk_size - 1, distance);
            current_position = disk_size - 1;
        }
        printf("Jump from %d -> 0 (Distance: %d)\n", 
               disk_size - 1, disk_size - 1);
        total_movement += disk_size - 1;
        current_position = 0;

        for (int i = 0; i < n; i++) {
            if (!serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }
    } else {

        for (int i = n-1; i >= 0; i--) {
            if (sorted[i] <= current_position && !serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }

        if (current_position != 0) {
            int distance = abs(0 - current_position);
            total_movement += distance;
            printf("Move from %d -> %d (Distance: %d)\n", 
                   current_position, 0, distance);
            current_position = 0;
        }
        printf("Jump from 0 -> %d (Distance: %d)\n", 
               disk_size - 1, disk_size - 1);
        total_movement += disk_size - 1;
        current_position = disk_size - 1;

        for (int i = n-1; i >= 0; i--) {
            if (!serviced[i]) {
                int distance = abs(sorted[i] - current_position);
                total_movement += distance;
                printf("Move from %d -> %d (Distance: %d)\n", 
                       current_position, sorted[i], distance);
                current_position = sorted[i];
                serviced[i] = 1;
            }
        }
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Seek Length: %.2f\n\n", (float)total_movement / n);
}

int main() {
    int n, head, direction, disk_size;
    
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
    
    printf("Enter initial direction (0 for left, 1 for right): ");
    scanf("%d", &direction);
    
    fifo(req, n, head);
    sstf(req, n, head);
    scan(req, n, head, direction, disk_size);
    cscan(req, n, head, direction, disk_size);

    return 0;
}