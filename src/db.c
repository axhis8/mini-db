#include "db.h"
#include <string.h>

entry database[SIZE_DB];
int database_count = 0;

entry *entry_get(const char *key) {
    for (int i = 0; i < database_count; i++) {
        if (strcmp(database[i].key, key) == 0) return &database[i];
    }

    return NULL;
}
