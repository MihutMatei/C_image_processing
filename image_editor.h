//311CA_MihutMatei_Tema3
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int r;
	int g;
	int b;
} pixel_t;

typedef struct {
	char type[4];
	int width;
	int height;
	int max_val;
	pixel_t **pixel_mat;
} image_t;

pixel_t **alloc_px_mat(int size1, int size2);
void free_mat(char **mat, int size);
void free_px_mat(pixel_t **mat, int size);

image_t load(char* filename);
void save(image_t* img, char* filename, bool is_ascii);
