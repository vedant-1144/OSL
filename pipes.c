#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
 
int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("You can not enter more or less than 3 arguments.\n");
        return 0;
    }
 
    int fd[2];
    int fork_val;
    char* file_1 = argv[1];
    char* file_2 = argv[2];
    int src_file;
    int dest_file;
 
    src_file = open(file_1, O_RDONLY);
    if(src_file == -1) {
        printf("Unable to open source file!!!\n");
        return 1;
    } else {
        dup2(src_file, STDIN_FILENO);
        close(src_file);
    }
 
    pipe(fd);
    fork_val = fork();
 
    if(fork_val > 0) {
        //Parent Process
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/sort", "sort", NULL);
        perror("execl failed for sort");
    }
    else if(fork_val == 0) {
        //Child Process
        dup2(fd[0], STDIN_FILENO);
        dest_file = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(dest_file == -1) {
            printf("Unable to open destination file!!!\n");
            return 1;
        } else {
            dup2(dest_file, STDOUT_FILENO);
            close(dest_file);
            close(fd[0]);
            close(fd[1]);
            execl("/usr/bin/uniq", "uniq", NULL);
            perror("execl failed for uniq");
        }
    } else {
        perror("Fork failed!!!");
        return 1;
    }
 
    return 0;
}