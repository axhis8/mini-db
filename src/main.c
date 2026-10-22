#include "cmd.h"
#include "db.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

int main() {
    char input[150];

    state s = CMD_OK;
    while (s != CMD_END) {
        // Inputs & Handling
        printf("> ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        if (strchr(input, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            fprintf(stderr, "%s input too large\n", ERR_PRX);
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        // Token Parsing
        char cmd[16], key[MAX_LEN_KEY + 1], val[MAX_LEN_VAL + 1];
        char *args[3] = {cmd, key, val};

        int n =
            sscanf(input, "%15s %" STR(MAX_LEN_KEY) "s %" STR(MAX_LEN_VAL) "s",
                   cmd, key, val);

        if (n < 1) continue;

        // Command Running
        s = run_command(n, args);
    }

    return 0;
}
