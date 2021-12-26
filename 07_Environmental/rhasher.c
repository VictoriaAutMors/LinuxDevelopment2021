#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <rhash.h>
#ifdef CONF_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif


size_t MAX_LEN = 1024;
char* MD5 = "MD5";
char* SHA1 = "SHA1";
char* TTH = "TTH";
int check_algorithm(char* cmd) {
    if (strcasecmp(cmd, MD5) == 0)
        return RHASH_MD5;
    if (strcasecmp(cmd, SHA1) == 0)
        return RHASH_SHA1;
    if (strcasecmp(cmd, TTH) == 0)
        return RHASH_TTH;
    return -1;
}

void print_hash(const char* input, unsigned int algorithm, int output_mode) {
    char digest[64];
    char out[MAX_LEN];
    if (input[0] == '"') {
        if (rhash_msg(algorithm, input + 1, strlen(input) - 2, digest) < 0) {
            fprintf(stderr, "Hash error in string\n");
            return;
        }
    } else {
        if (rhash_file(algorithm, in, digest) < 0) {
            fprintf(stderr, "Hash error in file\n");
            return;
        }
    }
    rhash_print_bytes(out, digest, rhash_get_digest_size(algorithm), output_mode);
    printf("%s\n", out);
}

int main(int argc, char const *argv[]) {
    rhash_library_init();
    char* input = (char*)malloc(sizeof(char) * MAX_LEN);
    #ifdef CONF_READLINE
    while ((input = readline(NULL)))
    #else
    while (getline(&input, &MAX_LEN, stdin) != -1) {
    #endif
        char* str_algorithm = strtok(input, " ");
        int algorithm = check_algorithm(str_algorithm);
        if (algorithm == -1) {
            continue;
        }
        int output_mode = isupper(str_algorithm[0]) ? RHPR_HEX : RHPR_BASE64;
        char* in = strtok(NULL, " ");
        if (!in) {
            continue;
        }
        char* trash = strtok(NULL, " ");
        if (trash) {
            fprintf(stderr, "\n" );
            continue;
        }
        if (in[strlen(in) - 1] == '\n') {
            in[strlen(in) - 1] = '\0';
        }
        print_hash(in, algorithm, output_mode);
    }
    return 0;
}

