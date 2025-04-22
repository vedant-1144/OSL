#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void display(int frame[], int frames, int page, bool hit) {
    printf("Page %d -> ", page);
    for (int i = 0; i < frames; i++) {
        if (frame[i] == -1) printf("- ");
        else printf("%d ", frame[i]);
    }
    printf(hit ? "(Hit)\n" : "(Fault)\n");
}

void fifo(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], index = 0, pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    
    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                hit = true;
                break;
            }
        }
        if (!hit) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            pageFaults++;
        }
        display(frame, frames, pages[i], hit);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

void lru(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], counter[MAX_FRAMES], time = 0, pageFaults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        counter[i] = -1;
    }
    
    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        bool hit = false;
        int minIdx = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                hit = true;
                counter[j] = time++;
                break;
            }
            if (frame[j] == -1 || counter[j] < counter[minIdx]) minIdx = j;
        }
        if (!hit) {
            frame[minIdx] = pages[i];
            counter[minIdx] = time++;
            pageFaults++;
        }
        display(frame, frames, pages[i], hit);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

void optimal(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    
    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                hit = true;
                break;
            }
        }
        if (!hit) {
            int replaceIndex = -1, farthest = i + 1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replaceIndex = j;
                    break;
                }
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) break;
                }
                if (k == n) {
                    replaceIndex = j;
                    break;
                }
                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
            }
            frame[replaceIndex == -1 ? 0 : replaceIndex] = pages[i];
            pageFaults++;
        }
        display(frame, frames, pages[i], hit);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, frames, choice, pages[MAX_PAGES];
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    while (true) {
        printf("\nChoose a Page Replacement Algorithm:\n1. FIFO\n2. LRU\n3. Optimal\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: fifo(pages, n, frames); break;
            case 2: lru(pages, n, frames); break;
            case 3: optimal(pages, n, frames); break;
            default: printf("Invalid choice!\n"); return 0;
        }
    }
    
    return 0;
}
