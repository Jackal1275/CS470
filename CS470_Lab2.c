#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define NUM_CHILDREN 10

// Commands for child processes
const char *commands[NUM_CHILDREN][3] = {
    {"echo", "Hello YourName", NULL},     // Unique echo task (include your name!)
    {"ls", "-l", NULL},
    {"date", NULL},
    {"whoami", NULL},
    {"pwd", NULL},
    {"uname", "-a", NULL},
    {"uptime", NULL},
    {"hostname", NULL},
    {"id", NULL},
    {"echo", "All child processes executed", NULL}
};

int main() {
    pid_t pids[NUM_CHILDREN];
    int status;

    printf("Parent PID: %d\n", getpid());

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) executing: %s\n", i + 1, getpid(), commands[i][0]);
            execvp(commands[i][0], (char *const *)commands[i]);
            // If execvp returns, there was an error
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process stores child PID
            pids[i] = pid;
        }
    }

    // Wait for all child processes
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t wpid = waitpid(pids[i], &status, 0);

        if (WIFEXITED(status)) {
            printf("Parent: Child with PID %d exited with status %d\n", wpid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent: Child with PID %d was terminated by signal %d\n", wpid, WTERMSIG(status));
        } else {
            printf("Parent: Child with PID %d ended abnormally\n", wpid);
        }
    }

    printf("All child processes completed.\n");
    return 0;
}
