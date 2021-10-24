#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void help() {
    printf("Program prints integer ranges: From M to N - 1 with step S\n");
    printf("Usage <./range [N]> or <./range [M] [N]> <./range [M] [N] [S]>\n");
}

void range(int M, int N, int S) {
    int i = M;
    for (i = M; i < N; i += S) {
        printf("%d\n", i);
    }
}

int main(int argc, char *argv[]) {      
    if (argc == 1) {
        printf("Wrong number of arguments. Use --help");
        return 0;
    }
    int M = 0;
    int N;
    int S = 1;
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            help();
            return 0;
        }
        N = atoi(argv[1]);
    }
    else if (argc == 3) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
    }
    else if (argc == 4) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        S = atoi(argv[3]);
    }
    else {
        printf("Incorrent parameters count. Use --help\n");
        return 1;
    }
    range(M, N, S);
    return 0;
}
