#include "cmd.h"
#include "storage.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    if (storage_load_db() != 0) return 1;

    char input[MAX_INPUT_LEN];

    state s = CMD_OK;
    while (s != CMD_END) {
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
        if (s == CMD_CHANGED) storage_append(input);
    }

    return 0;
}
