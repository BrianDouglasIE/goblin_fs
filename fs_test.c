#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "fs.h"

int main() {

    ///////////////////////////////////////
    // whats_at
    inode_type *test_dir = get_inode_type("./example_files");
    inode_type *test_file = get_inode_type("./example_files/hello_world.txt");
    inode_type *test_link = get_inode_type("./example_files/slink");
    inode_type *test_empty = get_inode_type("/does/not/exist");

    assert(test_dir->is_dir == 1);
    assert(test_dir->is_file == 0);
    assert(test_dir->is_link == 0);

    assert(test_file->is_dir == 0);
    assert(test_file->is_file == 1);
    assert(test_file->is_link == 0);

    assert(test_link->is_dir == 0);
    assert(test_link->is_file == 1);
    assert(test_link->is_link == 1);

    assert(test_empty == NULL);

    free(test_dir);
    free(test_file);
    free(test_link);
    free(test_empty);

    ///////////////////////////////////////
    // get_file_size
	assert(get_file_size("/does/not/exist.txt") == -1);
	assert(get_file_size("./example_files/14000.bin") == 14000);

    ///////////////////////////////////////
    // get_file_content
	assert(get_file_content("/does/not/exist.txt") == NULL);

	char *file_content = get_file_content("./example_files/hello_world.txt");
	puts(file_content);
	assert(strcmp(file_content, "hello world\n") == 0);
	free(file_content);

	return 0;
}
