#ifndef CMD_H
#define CMD_H

#define MAX_INPUT_LEN 150

typedef enum state { CMD_ERR = -1, CMD_OK, CMD_CHANGED, CMD_END } state;

state parse_command(const char *input);

#endif
