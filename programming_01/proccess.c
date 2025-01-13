#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void create_process_hierarchy(int depth, int max_children, FILE *output, int *process_count) {
    if (depth == 0 || max_children <= 0) {
        sleep(10 + (depth - 1));
        return;
    }

    pid_t children[max_children];
    for (int i = 0; i < max_children; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            (*process_count)++;
            create_process_hierarchy(depth - 1, max_children - 1, output, process_count);
            exit(EXIT_SUCCESS);
        } else {
            children[i] = pid;
        }
    }

    fprintf(output, "PID: %d Children: ", getpid());
    for (int i = 0; i < max_children; ++i) {
        fprintf(output, "%d ", children[i]);
    }
    fprintf(output, "\n");

    for (int i = 0; i < max_children; ++i) {
        waitpid(children[i], NULL, 0);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <N> [output_file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "N must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    FILE *output = stdout;
    if (argc >= 3) {
        output = fopen(argv[2], "w");
        if (!output) {
            perror("fopen");
            return EXIT_FAILURE;
        }
    }

    fprintf(output, "Author: Adodin Egor\n");
    int process_count = 1; // Считаем родительский процесс
    create_process_hierarchy(N, N, output, &process_count);

    // Финальный вывод от основного процесса
    fprintf(output, "Author: Adodin Egor\n");
    fprintf(output, "Total processes created: %d\n", process_count);

    if (output != stdout) {
        fclose(output);
    }

    return EXIT_SUCCESS;
}
