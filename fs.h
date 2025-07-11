#ifndef GOBLIN_FS_H
#define GOBLIN_FS_H

#include <stddef.h>

#ifndef MAX_FILE_SIZE_MB
#define MAX_FILE_SIZE_MB 1024  // 1GB in MB
#endif

#define MAX_FILE_SIZE ((long)(MAX_FILE_SIZE_MB) * 1024 * 1024)

typedef const char *Path;

typedef struct {
    int is_file;
    int is_dir;
    int is_link;
} InodeType;

InodeType *get_inode_type(Path path);

long get_file_size(Path path);

typedef struct {
    long size;
    char *data;
} FileContent;

FileContent *get_file_content(Path path);

void free_file_content(FileContent *fc);

#endif
