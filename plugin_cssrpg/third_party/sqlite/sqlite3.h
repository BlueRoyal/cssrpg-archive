#ifndef SQLITE3_H
#define SQLITE3_H
#include <stdarg.h>
#ifdef __cplusplus
extern "C" {
#endif

#define SQLITE_OK 0
#define SQLITE_ERROR 1

typedef struct sqlite3 sqlite3;

int sqlite3_open(const char *filename, sqlite3 **ppDb);
int sqlite3_close(sqlite3 *db);
char *sqlite3_vmprintf(const char *fmt, va_list ap);
int sqlite3_exec(sqlite3 *db, const char *sql,
                 int (*callback)(void*,int,char**,char**), void *arg,
                 char **errmsg);
void sqlite3_free(void *p);
int sqlite3_get_table(sqlite3 *db, const char *sql,
                      char ***resultp, int *nrow, int *ncol, char **errmsg);
void sqlite3_free_table(char **result);

#ifdef __cplusplus
}
#endif
#endif
