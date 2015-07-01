#ifndef SCANDIR_H
#define SCANDIR_H

#include "ignore.h"

typedef struct {
    const ignores *ig;
    const char *base_path;
    size_t base_path_len;
} scandir_baton_t;

typedef int (*filter_fp)(const char *path, const struct dirent *, void *);

#ifdef __cplusplus
extern "C" {
#endif

int ag_scandir(const char *dirname,
               struct dirent ***namelist,
               filter_fp filter,
               void *baton);
    
#ifdef __cplusplus
}
#endif

#endif
