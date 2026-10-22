#include <stdio.h>
#include <string.h>

static const char ERR_PRX[] = "error:";

int main() {
    char input[100];

    while (1) {
        // Inputs & Handling
        printf("> ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        if (strchr(input, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            fprintf(stderr, "%s input too large.\n", ERR_PRX);
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        // Token Parsing
        char cmd[16], key[64], val[64];
        int n = sscanf(input, "%15s %63s %63s", cmd, key, val);

        if (strcmp(cmd, "") == 0) {
            continue;
        }
        else if (strcmp(cmd, "exit") == 0) {
            break;
        }
        else if (strcmp(cmd, "list") == 0) {}
        else if (strcmp(cmd, "set") == 0) {
            if (n < 3) fprintf(stderr, "%s missing arguments.\n", ERR_PRX);
        }
        else {
            fprintf(stderr, "%s command not found: %s\n", ERR_PRX, cmd);
        }
    }

    return 0;
}
