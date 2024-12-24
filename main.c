#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum e_variant { Ternary };

typedef enum e_variant variant;

typedef char *value;

struct t_token {
  value *m_value;
  variant *m_variant;
};

void read_to_string(char *p_path, char *p_str) {
  FILE *p_fd = fopen(p_path, "rb");
  char *p_buf = 0;
  long size = 0;

  if (p_fd == NULL)
    return;
  fseek(p_fd, 0, SEEK_END);
  size = ftell(p_fd);
  fseek(p_fd, 0, SEEK_SET);
  p_buf = malloc(size + 1);
  if (p_buf)
    fread(p_buf, 1, size, p_fd);
  fclose(p_fd);
  p_buf[size] = '\0';
  strcpy(p_str, p_buf);
}

void err(char *p_str) { fprintf(stderr, "%s\n", p_str); }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    err("Error: Argument count invalid. (Expected at least 2)");
    return EXIT_FAILURE;
  }

  if (strlen(argv[1]) > (PATH_MAX + 1)) {
    err("Error: Path limit exceeded.");
    return EXIT_FAILURE;
  }

  char f_contents[4096] = {};
  char f_size;

  read_to_string(argv[1], f_contents);
  f_size = (int)strlen((const char *)f_contents);

  char buf[32] = {};
  int idx = 0;

  for (int i = 0; i < f_size; i++) {
    char c = f_contents[i];

    if (c == '\0') {
      idx = 0;
      memset(buf, 0, sizeof buf);
      continue;
    }

    buf[idx] = c;
    idx += 1;

    if (strcmp(buf, (const char *)"return") == 0) {
      fprintf(stdout, "Found return value.\n");
    }
  }

  return EXIT_SUCCESS;
}
