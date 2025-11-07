#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("ERROR: no arguments\n");
        return 1;
    }

    const char *word = argv[1];
    const char *file = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        printf("ERROR\n");
        return 2;
    }
    if (pid == 0) {
        char *args[] = {"grep", "-s", "-q", (char*)word, (char*)file, NULL};
        execv("/usr/bin/grep", args);
        _exit(127);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        int es = WEXITSTATUS(status);
        if (es == 0) {
            printf("FOUND: %s\n", word);
            return 0;
        } else if (es == 1) {
            printf("NOT FOUND: %s\n", word);
            return 0;
        } else if (es == 2) {
            printf("ERROR: %s doesn't exist\n", file);
            return 2;
        }
    }

    printf("ERROR\n");
    return 2;
}
