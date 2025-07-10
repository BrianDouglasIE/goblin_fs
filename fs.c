#include "fs.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

inode_type *inode_type_at(Path path) {
    inode_type *type = malloc(sizeof(inode_type));
    if(type == NULL) {
        perror("malloc");
        return NULL;
    }

    struct stat link_stat;
    if(lstat(path, &link_stat) == -1) {
        perror("lstat");
        free(type);
        return NULL;
    }

    type->is_link = S_ISLNK(link_stat.st_mode);

    struct stat st;
    if(stat(path, &st) == -1) {
        perror("stat");
        free(type);
        return NULL;
    }

    type->is_dir = S_ISDIR(st.st_mode);
    type->is_file = S_ISREG(st.st_mode);

    return type;
}

long get_file_size(Path path) {
  FILE *file = fopen(path, "rb");

  if (!file) {
    perror("fopen");
    return -1;
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    perror("fseek");
    fclose(file);
    return -1;
  }

  long file_size = ftell(file);
  if (file_size < 0) {
    perror("ftell");
    fclose(file);
    return -1;
  }

  fclose(file);
  return file_size;
}

char *get_file_content(Path path) {
  FILE *file = fopen(path, "rb");

  if (!file) {
    perror("fopen");
    return NULL;
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    perror("fseek");
    fclose(file);
    return NULL;
  }

  long file_size = ftell(file);
  if (file_size < 0) {
    perror("ftell");
    fclose(file);
    return NULL;
  }

  rewind(file);

  char *content = malloc(file_size + 1);
  if (!content) {
    perror("malloc");
    fclose(file);
    return NULL;
  }

  if (fread(content, file_size, 1, file) < 0) {
    perror("fread");
    fclose(file);
    free(content);
    return NULL;
  }

  fclose(file);

  content[file_size] = '\0';
  return content;
}
