#include <assert.h>
#include "fs.h"

int main() {
	char path_seperator = '/';
	goblin_fs *fs = fs_init(path_seperator);
	assert(fs != NULL);
	assert(fs->path_seperator == path_seperator);

	assert(is_dir(fs, "/does/not/exist") == -1);
	assert(is_file(fs, "/does/not/exist.txt") == -1);

	assert(get_file_size(fs, "/does/not/exist.txt") == -1);
	assert(get_file_size(fs, "./example_files/14000.bin") == 14000);

	assert(read_entire_file(fs, "/does/not/exist.txt") == NULL);

	fs_free(fs);
	fs = NULL;

	return 0;
}
