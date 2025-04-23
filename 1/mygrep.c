#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please Enter Correct Command !!!");
        exit(EXIT_FAILURE);
    }

    char *pattern = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No File Found, Error in Opening File !!! \n");
        exit(EXIT_FAILURE);
    }

    char line[1000];

    printf("Searching for pattern '%s' in '%s'...\n", pattern, filename);

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern)) {
            printf("%s",line);
        }
    }

    fclose(file);
    return 0;
}
