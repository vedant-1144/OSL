#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please Enter Correct Command !!!");
        exit(EXIT_FAILURE);
    }

    char *srcFile = argv[1];
    char *destFile = argv[2];

    FILE *src = fopen(srcFile, "r");
    if (!src) {
        printf("Error in Opening Source File");
        exit(EXIT_FAILURE);
    }

    FILE *dest = fopen(destFile, "w");
    if (!dest) {
        printf("Error in Opening Destination File");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char buffer[1000];
    int bytes;

    while (( bytes = fread(buffer, 1, 1000, src) ) > 0) {
        if ( fwrite(buffer, 1, bytes, dest) != bytes ) {
            printf("Error writing to destination file");
            fclose(src);
            fclose(dest);
            exit(EXIT_FAILURE);
        }
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully from '%s' to '%s'.\n", srcFile, destFile);
    return 0;
}