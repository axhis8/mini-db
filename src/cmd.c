#include "cmd.h"
#include "db.h"
#include "util.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef state (*cmd_fn)(int argc, char **argv);

typedef struct command {
    const char *name;
    cmd_fn fn;
} command;

static state cmd_list(int argc, char **argv) {
    (void)argc;
    (void)argv;

    size_t width = 0;
    for (int i = 0; i < database_count; i++) {
        size_t key_len = strlen(database[i].key);
        if (key_len > width) width = key_len;
    }

    for (int i = 0; i < database_count; i++) {
        printf("%4d. %-*s: %s\n", i + 1, (int)width, database[i].key,
               database[i].val);
    }

    return CMD_OK;
}

static state cmd_exit(int argc, char **argv) {
    (void)argc;
    (void)argv;

    return CMD_END;
}

static state cmd_set(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "%s missing arguments\n", ERR_PRX);
        return CMD_ERR;
    }

    entry *e = entry_get(argv[1]);

    if (e != NULL) {
        snprintf(e->val, sizeof(e->val), "%s", argv[2]);
    }
    else {
        if (database_count >= SIZE_DB) {
            fprintf(stderr, "%s database is full\n", ERR_PRX);
            return CMD_ERR;
        }

        e = &database[database_count];
        database_count++;

        snprintf(e->key, sizeof(e->key), "%s", argv[1]);
        snprintf(e->val, sizeof(e->val), "%s", argv[2]);
    }

    return CMD_OK;
}

static state cmd_get(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s missing key\n", ERR_PRX);
        return CMD_ERR;
    }

    entry *e = entry_get(argv[1]);

    if (e == NULL) {
        fprintf(stderr, "%s key not found: %s\n", ERR_PRX, argv[1]);
        return CMD_ERR;
    }

    printf("%s\n", e->val);
    return CMD_OK;
}

static state cmd_del(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "%s missing key\n", ERR_PRX);
        return CMD_ERR;
    }

    entry *e = entry_get(argv[1]);

    if (e == NULL) {
        fprintf(stderr, "%s key not found: %s\n", ERR_PRX, argv[1]);
        return CMD_ERR;
    }

    ptrdiff_t i = e - database;
    for (ptrdiff_t j = i; j < database_count - 1; j++) {
        database[j] = database[j + 1];
    }

    database_count--;
    return CMD_OK;
}

static const command commands[] = {
    {"list", cmd_list}, {"exit", cmd_exit}, {"set", cmd_set},
    {"get", cmd_get},   {"del", cmd_del},
};

state run_command(int argc, char **argv) {
    size_t count = sizeof(commands) / sizeof(commands[0]);
    for (size_t i = 0; i < count; i++) {
        if (strcmp(argv[0], commands[i].name) == 0)
            return commands[i].fn(argc, argv);
    }

    fprintf(stderr, "%s command not found: %s\n", ERR_PRX, argv[0]);
    return CMD_ERR;
}
