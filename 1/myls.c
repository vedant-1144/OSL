#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    const char *directory;

    if (argc == 2) {
        directory = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return EXIT_FAILURE;
    }

    DIR *dir = opendir(directory);
    if (dir == NULL) {
        perror("Opening Directory Failed failed");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    printf("Contents of Directory -> '%s':\n", directory);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return EXIT_SUCCESS;
}
