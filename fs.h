#include <stddef.h>

#ifndef GOBLIN_FS_H
#define GOBLIN_FS_H

typedef struct {
	char path_seperator;
} goblin_fs;

typedef const char *Path;

goblin_fs *fs_init(char path_seperator);
void fs_free(goblin_fs *fs);

int is_dir(goblin_fs *fs,  Path path);
int is_file(goblin_fs *fs,  Path path);
int get_file_size(goblin_fs *fs,  Path path);

const char *read_entire_file(goblin_fs *fs,  Path path);

#endif
