#ifndef GOBLIN_FS_H
#define GOBLIN_FS_H

#include <stddef.h>
typedef const char *Path;

typedef struct {
    int is_file;
    int is_dir;
    int is_link;
} inode_type;

inode_type *inode_type_at(Path path);

long get_file_size(Path path);

char *get_file_content(Path path);

#endif
