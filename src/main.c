#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef int (*cmd_fn)(int argc, char **argv);

typedef struct command {
    const char *name;
    cmd_fn fn;
} command;

static const char ERR_PRX[] = "error:";

// TODO: Set Data
static int cmd_set(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "%s missing arguments.\n", ERR_PRX);
        return 1;
    }

    return 0;
}

// TODO: List Data
static int cmd_list(int argc, char **argv) {
    (void)argc;
    (void)argv;
    return 0;
}

static const command commands[] = {
    {"set", cmd_set},
    {"list", cmd_list},
};

static int run_command(int argc, char **argv) {
    size_t count = sizeof(commands) / sizeof(commands[0]);
    for (size_t i = 0; i < count; i++) {
        if (strcmp(argv[0], commands[i].name) == 0)
            return commands[i].fn(argc, argv);
    }

    fprintf(stderr, "%s command not found: %s\n", ERR_PRX, argv[0]);
    return 1;
}

int main() {
    char input[150];

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
        char *args[3] = {cmd, key, val};

        int n = sscanf(input, "%15s %63s %63s", cmd, key, val);
        if (n < 1) continue;
        if (strcmp(cmd, "exit") == 0) break;

        // Command Running
        run_command(n, args);
    }

    return 0;
}
