#include "cmd.h"
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

        s = parse_command(input);
    }

    return 0;
}
