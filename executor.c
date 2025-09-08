// executor.c - Runs the target program and monitors exit code/signals
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "executor.h"

#define TMP_INPUT_FILE "/tmp/fuzz_input.bin"

int executor_run(const char *target, const unsigned char *input, size_t len, int timeout, int *exit_status, int *signal_out) {
    pid_t pid = fork();
    if (pid < 0) return EXECUTOR_ERROR;
    if (pid == 0) {
        // Child: write input to stdin
        int fd = open(TMP_INPUT_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
        if (fd < 0) exit(101);
        write(fd, input, len);
        close(fd);
        int in_fd = open(TMP_INPUT_FILE, O_RDONLY);
        if (in_fd < 0) exit(102);
        dup2(in_fd, 0); // Redirect stdin
        close(in_fd);
        execl(target, target, NULL);
        exit(103);
    }
    // Parent
    int status = 0;
    int waited = 0;
    for (int i = 0; i < timeout * 10; i++) {
        usleep(100000);
        waited += 100000;
        pid_t res = waitpid(pid, &status, WNOHANG);
        if (res == pid) break;
    }
    if (waited >= timeout * 1000000) {
        kill(pid, SIGKILL);
        waitpid(pid, &status, 0);
    }
    if (WIFSIGNALED(status)) {
        *signal_out = WTERMSIG(status);
        *exit_status = -1;
        return EXECUTOR_CRASH;
    } else if (WIFEXITED(status)) {
        *exit_status = WEXITSTATUS(status);
        *signal_out = 0;
        if (*exit_status != 0) return EXECUTOR_CRASH;
        return EXECUTOR_OK;
    }
    return EXECUTOR_ERROR;
}
