#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct sqlite3 { int dummy; };

int sqlite3_open(const char *filename, sqlite3 **ppDb) {
    (void)filename;
    *ppDb = (sqlite3*)calloc(1, sizeof(sqlite3));
    return SQLITE_OK;
}

int sqlite3_close(sqlite3 *db) {
    free(db);
    return SQLITE_OK;
}

char *sqlite3_vmprintf(const char *fmt, va_list ap) {
    char *buf = NULL;
    if (vasprintf(&buf, fmt, ap) == -1) {
        return NULL;
    }
    return buf;
}

int sqlite3_exec(sqlite3 *db, const char *sql,
                 int (*callback)(void*,int,char**,char**), void *arg,
                 char **errmsg) {
    (void)db; (void)sql; (void)callback; (void)arg;
    if (errmsg) *errmsg = NULL;
    return SQLITE_OK;
}

void sqlite3_free(void *p) { free(p); }

int sqlite3_get_table(sqlite3 *db, const char *sql,
                      char ***resultp, int *nrow, int *ncol, char **errmsg) {
    (void)db; (void)sql;
    if (resultp) *resultp = NULL;
    if (nrow) *nrow = 0;
    if (ncol) *ncol = 0;
    if (errmsg) *errmsg = NULL;
    return SQLITE_OK;
}

void sqlite3_free_table(char **result) { free(result); }
