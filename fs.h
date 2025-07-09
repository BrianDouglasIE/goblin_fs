#ifndef GOBLIN_FS_H
#define GOBLIN_FS_H

#include <stddef.h>
typedef const char *Path;

int is_dir( Path path);
int is_file(Path path);
int is_link(Path path);
long get_file_size(Path path);

char *get_file_content(Path path);

#endif
