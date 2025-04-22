#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    const char *directory;

    if (argc == 1) {
        directory = ".";
    } else if (argc == 2) {
        directory = argv[1];
    } else {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return EXIT_FAILURE;
    }

    DIR *dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir failed");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    printf("Contents of directory '%s':\n", directory);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return EXIT_SUCCESS;
}
