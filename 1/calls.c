#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void simulate_cp(const char *source, const char *destination) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child (cp): PID=%d, Parent PID=%d\n", getpid(), getppid());
        execlp("./mycp", "mycp", source, destination, NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("\nParent: Completed cp command.\n");
    }
}

void simulate_grep(const char *pattern, const char *file) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child (grep): PID=%d, Parent PID=%d\n", getpid(), getppid());
        execlp("./mygrep", "mygrep", pattern,  file, NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("\nParent: Completed grep command.\n");
    }
}

void simulate_ls(const char *directory) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("Child (ls): PID=%d, Parent PID=%d\n", getpid(), getppid());
        execlp("./myls", "myls", directory, NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("\nParent: Completed ls command.\n");
    }
}

int main() {
    int choice;
    char source[100], destination[100], pattern[100], file[100];

    printf("Select a command to simulate:\n");
    printf("1. cp (copy file)\n");
    printf("2. grep (search in file)\n");
    printf("3. ls (Listing Content Of Directory)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter source file: ");
            scanf("%s", source);
            printf("Enter destination file: ");
            scanf("%s", destination);
            simulate_cp(source, destination);
            break;

        case 2:
            printf("Enter pattern to search: ");
            scanf("%s", pattern);
            printf("Enter file to search in: ");
            scanf("%s", file);
            simulate_grep(pattern, file);
            break;

        case 3:
            printf("Enter Directory to List: ");
            scanf("%s", source);
            simulate_ls(source);
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }

    printf("\nParent: All processes completed. Exiting...\n");
    return 0;
}
