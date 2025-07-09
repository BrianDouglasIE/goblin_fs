#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "fs.h"

int main() {
    assert(is_dir("/does/not/exist") == -1);
    assert(is_dir("./example_files") == 1);
	assert(!is_dir("./example_files/hello_world.txt"));
	assert(!is_dir("./example_files/slink.txt"));

	assert(is_file("/does/not/exist.txt") == -1);
	assert(is_file("./example_files/hello_world.txt") == 1);
	assert(!is_file("./example_files"));
	assert(!is_file("./example_files/slink.txt"));

	assert(is_link("/does/not/exist.txt") == -1);
	assert(is_link("./example_files/slink.txt") == 1);
	assert(!is_link("./example_files"));
	assert(!is_link("./example_files/hello_world.txt"));

	assert(get_file_size("/does/not/exist.txt") == -1);
	assert(get_file_size("./example_files/14000.bin") == 14000);

	assert(get_file_content("/does/not/exist.txt") == NULL);

	char *file_content = get_file_content("./example_files/hello_world.txt");
	puts(file_content);
	assert(strcmp(file_content, "hello world\n") == 0);
	free(file_content);

	return 0;
}
