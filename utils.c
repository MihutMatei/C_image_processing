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
	for(int i = 0; i < size2; i ++) {
		mat[i] = (pixel_t*) malloc(size2 * sizeof(pixel_t));
		if(!mat[i]) {
			fprintf(stderr, "alloc failure\n");
			for(int j = 0; j < i; j++) {
				free(mat[j]);
			}
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


image_t load(char* filename)
{
	image_t img = {0};
	FILE *in = fopen(filename, "rt");

	if (!in) {
		printf("Failed to load 1 %s\n", filename);
		return img;
	}

	fscanf(in, "%s", img.type);
	fscanf(in, "%d %d", &img.width, &img.height);
	fscanf(in, "%d", &img.max_val);

	img.pixel_mat = alloc_px_mat(img.width, img.height);

	if (img.type[1] == '1' || img.type[1] == '2'|| img.type[1] == '3') {
		for (int i = 0; i < img.width; i++) {
			for (int j = 0; j < img.height; j++) {
				if(fscanf(in, "%d %d %d",
				   &img.pixel_mat[i][j].r,
				   &img.pixel_mat[i][j].g,
				   &img.pixel_mat[i][j].b) != 3) {
					printf("Failed to load 2 %s\n", filename);
					free_px_mat(img.pixel_mat, img.width);
					strcpy(img.type,"");
					img.height = 0;
					img.width = 0;
					img.max_val = 0;
					return img;
				}
			}
		}
		fclose(in);
	} else if (img.type[1] == '4' || img.type[1] == '5' || img.type[1] == '6') {
		for (int i = 0; i < img.width; i++) {
			for (int j = 0; j < img.height; j++) {
				if (fread(&img.pixel_mat[i][j].r, sizeof(char), 1, in) != 1 ||
					fread(&img.pixel_mat[i][j].g, sizeof(char), 1, in) != 1 ||
					fread(&img.pixel_mat[i][j].b, sizeof(char), 1, in) != 1) {
						printf("Failed to load 3 %s\n", filename);
						free_px_mat(img.pixel_mat, img.width);
						strcpy(img.type,"");
						img.height = 0;
						img.width = 0;
						img.max_val = 0;
						fclose(in);
						return img;
				}
			}
		}
	} else {
		//to fix
		printf("Failed to load 4 %s\n", filename);
		free_px_mat(img.pixel_mat, img.width);
		strcpy(img.type,"");
		img.height = 0;
		img.width = 0;
		img.max_val = 0;
		return img;
	}

	printf("Loaded %s\n", filename);

	return img;
}

void save(image_t* img, char* filename, bool is_ascii)
{
	FILE *out = fopen(filename, "wt");

	fprintf(out, "%s\n", img->type);
	fprintf(out, "%d %d\n", img->width, img->height);
	fprintf(out, "%d\n", img->max_val);

	fclose(out);
	out = fopen(filename, "wb");
	fseek(out, 0, SEEK_END);

	if (is_ascii) {
		for (int i = 0; i < img->width; i++) {
			for (int j = 0; j < img->height; j++) {
				fprintf(out, "%d %d %d\n",
					img->pixel_mat[i][j].r,
					img->pixel_mat[i][j].g,
					img->pixel_mat[i][j].b);
			}
		}
	} else {
		for (int i = 0; i < img->width; i++) {
			for (int j = 0; j < img->height; j++) {
				fwrite(&img->pixel_mat[i][j].r, sizeof(char), 1, out);
				fwrite(&img->pixel_mat[i][j].g, sizeof(char), 1, out);
				fwrite(&img->pixel_mat[i][j].b, sizeof(char), 1, out);
			}
		}
	}
	fclose(out);
}
