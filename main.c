#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

enum
e_variant {
	Ternary
};

typedef
enum e_variant	variant;

typedef
char*		value;

struct
t_token {
	value* 		m_value;
	variant* 	m_variant;
};

void
read_to_string(char* p_path, char* p_str)
{
	FILE *p_fd  = fopen(p_path, "rb");
	char *p_buf = 0;
	long size   = 0;

	if (p_fd == NULL) return;
	fseek(p_fd, 0, SEEK_END);
	size = ftell(p_fd);
	fseek(p_fd, 0, SEEK_SET);
	p_buf = malloc(size + 1);
	if (p_buf) fread(p_buf, 1, size, p_fd);
	fclose(p_fd);
	p_buf[size] = '\0';
	strcpy(p_str, p_buf);
}

void
err(char* p_str, int* p_ecode)
{
	fprintf(stderr, "%s\n", p_str);
	if (p_ecode != NULL) exit(*p_ecode);
}

int
main(int argc, char* argv[])
{
	if (argc < 2)
		err("Error: Argument count invalid. (Expected at least 2)", (int*)1);

	if (strlen(argv[1]) > (PATH_MAX + 1))
		err("Error: Path limit exceeded.", (int*)1);

	char f_contents[4096] = {};

	read_to_string(argv[1], f_contents);

	printf("%s", f_contents);

	return EXIT_SUCCESS;
}
