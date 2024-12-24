//311CA_MihutMatei_Tema3
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

pixel_t **alloc_px_mat(int size1, int size2);
void free_mat(void **mat);

image_t load(char* filename);