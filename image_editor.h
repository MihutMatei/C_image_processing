#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int r;
	int g;
	int b;
} pixel_t;

typedef struct {
	char *type;
	int width;
	int height;
	int max_val;
	pixel_t **pixel_mat;
} image_t;

int is_binary_file(char *filename);
void load(char* filename);