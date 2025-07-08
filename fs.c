#include "fs.h"
#include <stdio.h>
#include <stdlib.h>

goblin_fs *fs_init(char path_seperator) {
	goblin_fs *fs = malloc(sizeof(goblin_fs));
	if(!fs) return NULL;

	fs->path_seperator = path_seperator;
	return fs;
}

void fs_free(goblin_fs *fs) {
	if(fs == NULL) return;
	free(fs);
}


int is_dir(goblin_fs *fs,  Path path) {
	return -1;
}

int is_file(goblin_fs *fs,  Path path) {
	return -1;
}

int get_file_size(goblin_fs *fs,  Path path) {
	FILE *file = fopen(path, "rb");
	if(!file) {
		perror("fopen");
		return -1;
	}

	if(fseek(file, 0, SEEK_END) != 0) {
		perror("fseek");
		fclose(file);
		return -1;
	}

	int file_size = ftell(file);
	if(file_size < 0) {
		perror("ftell");
		fclose(file);
		return -1;
	}

	return file_size;
}

const char *read_entire_file(goblin_fs *fs,  Path path) {
	return NULL;
}
