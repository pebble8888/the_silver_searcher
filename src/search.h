#ifndef SEARCH_H
#define SEARCH_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mutex>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#include "ignore.h"
#include "log.h"
#include "options.h"
#include "print.h"
#include "util.h"
#include "uthash.h"

struct work_queue_t {
    char *path;
    struct work_queue_t *next;
};
typedef struct work_queue_t work_queue_t;

/* For symlink loop detection */
#define SYMLOOP_ERROR (-1)
#define SYMLOOP_OK (0)
#define SYMLOOP_LOOP (1)

typedef struct {
    dev_t dev;
    ino_t ino;
} dirkey_t;

typedef struct {
    dirkey_t key;
    UT_hash_handle hh;
} symdir_t;

extern size_t alpha_skip_lookup[256];
extern size_t *find_skip_lookup;
extern work_queue_t *      m_work_queue;
extern work_queue_t *      m_work_queue_tail;
extern int                 m_done_adding_files;
extern std::condition_variable m_files_ready_cond;
extern std::mutex          m_print_mtx;
extern std::mutex          m_stats_mtx;
extern std::mutex          m_work_queue_mtx;
extern symdir_t *symhash;

#ifdef __cplusplus
extern "C" {
#endif

void search_stream(FILE *stream, const char *path);
void *search_file_worker(void *i);
void search_dir(ignores *ig, const char *base_path, const char *path, const int depth, dev_t original_dev);
    
#ifdef __cplusplus
}
#endif

#endif
