//311CA_MihutMatei_Tema3
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} pixel_t;

typedef struct {
	char type[4];
	int width;
	int height;
	int max_val;
	pixel_t **pixel_mat;
} image_t;

typedef struct {
	int x1, y1, x2, y2;
} selection_t;

pixel_t **alloc_px_mat(int size1, int size2);
void free_px_mat(pixel_t **mat, int size);

image_t load(char *filename);
void save(image_t *img, char *filename, bool is_ascii);

void handle_select(image_t *img, selection_t *selection, char *argument);
void set_selection_all(image_t *img, selection_t *selection);

bool is_selection_square(selection_t *selection);
bool is_selection_all(image_t *img, selection_t *selection);

void rotate(image_t *img, selection_t *selection, int angle);
void handle_rotate(image_t *img, selection_t *selection, char *buffer);
void crop(image_t *img, selection_t *selection);
void histogram(image_t *img, selection_t *selection, int x, int y);
void handle_histogram(image_t *img, selection_t *selection, char *buffer);
void equalize(image_t *img);
void apply_filter(image_t *img, selection_t *selection, char *argument);
void apply_edge(image_t *img, selection_t *selection);
void apply_sharpen(image_t *img, selection_t *selection);
void apply_box_blur(image_t *img, selection_t *selection);
void apply_gaussian_blur(image_t *img, selection_t *selection);

image_t load_pgm(FILE *in, image_t *img);
image_t load_ppm(FILE *in, image_t *img);
image_t load_bw(FILE *in, image_t *img);
image_t load_binary_pgm(FILE *in, image_t *img);
image_t load_binary_ppm(FILE *in, image_t *img);
image_t load_binary_bw(FILE *in, image_t *img);

int clamp(int value);
