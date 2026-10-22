#include <stdio.h>
#include <string.h>

static const char ERR_PRX[] = "error:";

int main() {
    char input[100];

    while (1) {
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

        if (strcmp(input, "exit") == 0) break;

        printf("%s\n", input);
    }

    return 0;
}
