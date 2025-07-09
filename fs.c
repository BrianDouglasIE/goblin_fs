#include "fs.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int is_link(Path path) {
    struct stat st;
    if(lstat(path, &st) == -1) {
        perror("lstat");
        return -1;
    }

    return S_ISLNK(st.st_mode);
}

int is_dir(Path path) {
    int link_result = is_link(path);
    if (link_result) {
        return link_result < 0 ? -1 : 0;
    }

    struct stat st;
    if(stat(path, &st) == -1) {
        perror("stat");
        return -1;
    }

    return S_ISDIR(st.st_mode);
}

int is_file(Path path) {
    int link_result = is_link(path);
    if (link_result) {
        return link_result < 0 ? -1 : 0;
    }

    struct stat st;
    if(stat(path, &st) == -1) {
        perror("stat");
        return -1;
    }

    return S_ISREG(st.st_mode);
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
