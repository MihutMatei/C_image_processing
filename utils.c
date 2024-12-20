#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "image_editor.h"

int is_binary_file(char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (file == NULL)
	{
		return 0;
	}

	for(int i = 0; i < 100; i++)
	{
		int c = fgetc(file);
		if (c == EOF)
		{
			break;
		}
		if (c == '\0')
		{
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	return 0;
}

image_t load(char* filename)
{
	image_t img;

	if(is_binary_file(filename)) {
		FILE *in = fopen(filename, "rb");
		fread(&img.type, sizeof(char), 2, in);
		fread(&img.width, sizeof(int), 1, in);
		fread(&img.height, sizeof(int), 1, in);
		fread(&img.max_val, sizeof(int), 1, in);
		for(int i = 0; i < img.width; i ++) {
			for(int j = 0; j < img.height; j++) {
				fread(&img.pixel_mat[i][j].r, sizeof(int), 1, in);
				fread(&img.pixel_mat[i][j].g, sizeof(int), 1, in);
				fread(&img.pixel_mat[i][j].b, sizeof(int), 1, in);
			}
		}
		fclose(in);
	}
	else {
		FILE *in = fopen(filename, "rt");
		fscanf(in, "%s", img.type);
		fscanf(in, "%d %d", &img.width, &img.height);
		fscanf(in, "%d", &img.max_val);
		for(int i = 0; i < img.width; i ++) {
			for(int j = 0; j < img.height; j++) {
				fscanf(in, "%d %d %d", &img.pixel_mat[i][j].r, &img.pixel_mat[i][j].g, &img.pixel_mat[i][j].b);
			}
		}
		fclose(in);
	}
	return img;
}
