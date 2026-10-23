#include "cmd.h"
#include "util.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

static const char save_file[] = "data.aof";

int storage_append(const char *input) {
    FILE *f = fopen(save_file, "a");
    if (f == NULL) {
        print_file_err(save_file);
        return -1;
    }

    fprintf(f, "%s\n", input);
    fclose(f);

    return 0;
}

int storage_load_db(void) {
    FILE *f = fopen(save_file, "r");
    if (f == NULL) {
        if (errno == ENOENT) {
            f = fopen(save_file, "a");
            if (f == NULL) {
                print_file_err(save_file);
                return -1;
            }
            fclose(f);
            return 0;
        }
        else {
            print_file_err(save_file);
            return -1;
        }
    }

    char input[MAX_INPUT_LEN];
    while (fgets(input, sizeof(input), f) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        parse_command(input);
    }
    fclose(f);

    return 0;
}
