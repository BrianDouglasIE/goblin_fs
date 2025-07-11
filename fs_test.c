#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "fs.h"

int main() {

    ///////////////////////////////////////
    // whats_at
    InodeType *test_dir = get_inode_type("./example_files");
    InodeType *test_file = get_inode_type("./example_files/hello_world.txt");
    InodeType *test_link = get_inode_type("./example_files/slink");
    InodeType *test_empty = get_inode_type("/does/not/exist");

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

	FileContent *content = get_file_content("./example_files/hello_world.txt");
	assert(content->size == 12);
	assert(strcmp(content->data, "hello world\n") == 0);
	free_file_content(content);

	return 0;
}
