#ifndef CMD_H
#define CMD_H

typedef enum state { CMD_OK = 0, CMD_ERR, CMD_END } state;

state parse_command(const char *input);

#endif
