#include "util.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

const char ERR_PRX[] = "error:";

static void print_err_lower(const char *msg) {
    for (int j = 0; msg[j] != '\0'; j++) fputc(tolower(msg[j]), stderr);
}

void print_file_err(const char save_file[]) {
    const char *msg = strerror(errno);
    fprintf(stderr, "%s %s: ", ERR_PRX, save_file);
    print_err_lower(msg);
    fputc('\n', stderr);
}
