#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

static void say(const char *s) {
    write(STDOUT_FILENO, s, strlen(s));
    write(STDOUT_FILENO, "\n", 1);
}

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        say("ERROR: no arguments");
        return 1;
    }

    int n = argc - 1;
    int first_idx, count;
    if (n % 2 == 1) {
        first_idx = 1 + n / 2;
        count = 1;
    } else {
        first_idx = 1 + (n / 2 - 1);
        count = 2;
    }

    char *eargs[4];
    eargs[0] = "echo";
    eargs[1] = (char*)argv[first_idx];
    if (count == 2) {
        eargs[2] = (char*)argv[first_idx + 1];
        eargs[3] = NULL;
    } else {
        eargs[2] = NULL;
        eargs[3] = NULL;
    }

    int rc = execv("/bin/echo", eargs);
    (void)rc;
    say("exec error");
    return 1;
}
