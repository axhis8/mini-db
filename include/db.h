#ifndef DB_H
#define DB_H

#define SIZE_DB 1024
#define MAX_LEN_KEY 63
#define MAX_LEN_VAL 63

typedef struct entry {
    char key[MAX_LEN_KEY + 1];
    char val[MAX_LEN_VAL + 1];
} entry;

entry *entry_get(const char *key);

extern entry database[SIZE_DB];
extern int database_count;

#endif
