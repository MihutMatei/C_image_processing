//311CA_MihutMatei_Tema3
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "image_editor.h"

pixel_t **alloc_px_mat(int size1, int size2)
{
	pixel_t **mat = (pixel_t**) malloc(size1 * sizeof(pixel_t *));
	if(!mat) {
		fprintf(stderr, "alloc failure\n");
		return NULL;
	}
	for(int i = 0; i < size1; i++) {
		mat[i] = (pixel_t*) calloc(size2, sizeof(pixel_t)); // Use calloc to initialize memory to zero
		if(!mat[i]) {
			fprintf(stderr, "alloc failure\n");
			for(int j = 0; j < i; j++) {
				free(mat[j]);
			}
			free(mat); // Free the allocated memory for mat
			return NULL;
		}
	}
	return mat;
}


void free_mat(char **mat, int size)
{
	for(int i = 0; i < size; i++) {
		free(mat[i]);
	}
	free(mat);
}

void free_px_mat(pixel_t **mat, int size)
{
	for(int i = 0; i < size; i++) {
		free(mat[i]);
	}
	free(mat);
}

image_t load_pgm(FILE *in, image_t *img) {
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			int value;
			if(fscanf(in, "%d", &value) != 1) {
				printf("Failed to load PGM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
			img->pixel_mat[i][j].r = (unsigned char)value;
			img->pixel_mat[i][j].g = img->pixel_mat[i][j].r;
			img->pixel_mat[i][j].b = img->pixel_mat[i][j].r;
			if (img->pixel_mat[i][j].r > img->max_val) {
				printf("Failed to load PGM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
				}
			}
		}
		return *img;
	}

image_t load_ppm(FILE *in, image_t *img) {
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			int r, g, b;
			if(fscanf(in, "%d %d %d", &r, &g, &b) != 3) {
				printf("Failed to load PPM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
			img->pixel_mat[i][j].r = (unsigned char)r;
			img->pixel_mat[i][j].g = (unsigned char)g;
			img->pixel_mat[i][j].b = (unsigned char)b;
			if (img->pixel_mat[i][j].r > img->max_val ||
				img->pixel_mat[i][j].g > img->max_val ||
				img->pixel_mat[i][j].b > img->max_val) {
				printf("Failed to load PPM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
		}
	}
	return *img;
}

image_t load_bw(FILE *in, image_t *img) {
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			int value;
			if(fscanf(in, "%d", &value) != 1) {
				printf("Failed to load BW\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
			img->pixel_mat[i][j].r = (unsigned char)value;
			img->pixel_mat[i][j].g = img->pixel_mat[i][j].r;
			img->pixel_mat[i][j].b = img->pixel_mat[i][j].r;
			if (img->pixel_mat[i][j].r > 1) {
				printf("Failed to load BW\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
		}
	}
	return *img;
}

image_t load_binary_pgm(FILE *in, image_t *img) {
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			if (fread(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, in) != 1) {
				printf("Failed to load binary PGM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
			img->pixel_mat[i][j].g = img->pixel_mat[i][j].r;
			img->pixel_mat[i][j].b = img->pixel_mat[i][j].r;
			if (img->pixel_mat[i][j].r > img->max_val) {
				printf("Failed to load binary PGM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
		}
	}
	return *img;
}

image_t load_binary_ppm(FILE *in, image_t *img) {
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			if (fread(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, in) != 1 ||
				fread(&img->pixel_mat[i][j].g, sizeof(unsigned char), 1, in) != 1 ||
				fread(&img->pixel_mat[i][j].b, sizeof(unsigned char), 1, in) != 1) {
				printf("Failed to load binary PPM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
			if (img->pixel_mat[i][j].r > img->max_val ||
				img->pixel_mat[i][j].g > img->max_val ||
				img->pixel_mat[i][j].b > img->max_val) {
				printf("Failed to load binary PPM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
		}
	}
	return *img;
}

image_t load_binary_bw(FILE *in, image_t *img) {
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			if (fread(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, in) != 1) {
				printf("Failed to load binary BW\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
			img->pixel_mat[i][j].g = img->pixel_mat[i][j].r;
			img->pixel_mat[i][j].b = img->pixel_mat[i][j].r;
			if (img->pixel_mat[i][j].r > 1) {
				printf("Failed to load binary BW\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
				fclose(in);
				return *img;
			}
		}
	}
	return *img;
}

image_t load(char* filename)
{
	image_t img = {0};
	FILE *in = fopen(filename, "rb");

	if (!in) {
		printf("Failed to load %s\n", filename);
		return img;
	}

	fscanf(in, "%s", img.type);
	fscanf(in, "%d %d", &img.width, &img.height);
	fscanf(in, "%d", &img.max_val);

	img.pixel_mat = alloc_px_mat(img.height, img.width);

	if (img.type[1] == '1') {
		img = load_bw(in, &img);
	} else if (img.type[1] == '2') {
		img = load_pgm(in, &img);
	} else if (img.type[1] == '3') {
		img = load_ppm(in, &img);
	} else if (img.type[1] == '4') {
		fgetc(in); // consume the newline character after max_val
		img = load_binary_bw(in, &img);
	} else if (img.type[1] == '5') {
		fgetc(in); // consume the newline character after max_val
		img = load_binary_pgm(in, &img);
	} else if (img.type[1] == '6') {
		fgetc(in); // consume the newline character after max_val
		img = load_binary_ppm(in, &img);
	} else {
		printf("Failed to load %s\n", filename);
		free_px_mat(img.pixel_mat, img.height);
		strcpy(img.type,"");
		img.height = 0;
		img.width = 0;
		img.max_val = 0;
		fclose(in);
		return img;
	}

	fclose(in);
	printf("Loaded %s\n", filename);

	return img;
}

void save(image_t *img, char* filename, bool is_ascii)
{
	if (is_ascii) {
		FILE *out = fopen(filename, "wt");

		if (!out) {
			printf("Failed to save %s\n", filename);
			return;
		}

		fprintf(out, "%s\n", img->type);
		fprintf(out, "%d %d\n", img->width, img->height);
		fprintf(out, "%d\n", img->max_val);

		if(img->type[1] == '1' || img->type[1] == '2') {
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fprintf(out, "%d ", img->pixel_mat[i][j].r);
				}
				fprintf(out, "\n");
			}
		} else if(img->type[1] == '3') {
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fprintf(out, "%d %d %d ",
						img->pixel_mat[i][j].r,
						img->pixel_mat[i][j].g,
						img->pixel_mat[i][j].b);
				}
				fprintf(out, "\n");
			}
		}

		fclose(out);
		printf("Saved %s\n", filename);

	} else {
		FILE *out = fopen(filename, "wb");
		if(!out) {
			printf("Failed to save %s\n", filename);
			return;
		}
		fprintf(out, "%s\n", img->type);
		fprintf(out, "%d %d\n", img->width, img->height);
		fprintf(out, "%d\n", img->max_val);

		if(img->type[1] == '4' || img->type[1] == '5') {
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fwrite(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, out);
				}
			}
		} else if(img->type[1] == '6') {
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fwrite(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, out);
					fwrite(&img->pixel_mat[i][j].g, sizeof(unsigned char), 1, out);
					fwrite(&img->pixel_mat[i][j].b, sizeof(unsigned char), 1, out);
				}
			}
		}
		fclose(out);
		printf("Saved %s\n", filename);
	}
}
