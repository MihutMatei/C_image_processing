//311CA_MihutMatei_Tema3
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
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

void free_px_mat(pixel_t **mat, int size)
{
    if (mat) {
        for (int i = 0; i < size; i++) {
            if (mat[i]) {
                free(mat[i]);
            }
        }
        free(mat);
    }
	mat = NULL;
}

image_t load_pgm(FILE *in, image_t *img)
{
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
				return *img;
			}
		}
	}
	return *img;
}

image_t load_ppm(FILE *in, image_t *img)
{
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
				return *img;
			}
		}
	}
	return *img;
}

image_t load_bw(FILE *in, image_t *img)
{
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
				return *img;
			}
		}
	}
	return *img;
}

image_t load_binary_pgm(FILE *in, image_t *img)
{
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			if (fread(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, in) != 1) {
				printf("Failed to load binary PGM\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
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
				return *img;
			}
		}
	}
	return *img;
}

image_t load_binary_ppm(FILE *in, image_t *img)
{
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
				return *img;
			}
		}
	}
	return *img;
}

image_t load_binary_bw(FILE *in, image_t *img)
{
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			if (fread(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, in) != 1) {
				printf("Failed to load binary BW\n");
				free_px_mat(img->pixel_mat, img->height);
				strcpy(img->type,"");
				img->height = 0;
				img->width = 0;
				img->max_val = 0;
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
		img.pixel_mat = NULL;
		return img;
	}

	fscanf(in, "%s", img.type);
	fscanf(in, "%d %d", &img.width, &img.height);
	fscanf(in, "%d", &img.max_val);

	// Free previously allocated memory if it exists
	if (img.pixel_mat) {
		free_px_mat(img.pixel_mat, img.height);
		img.pixel_mat = NULL;
	}

	img.pixel_mat = alloc_px_mat(img.height, img.width);
	if (!img.pixel_mat) {
		fclose(in);
		printf("Failed to allocate memory for image\n");
		return img;
	}

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
		if(img.pixel_mat) {
			free_px_mat(img.pixel_mat, img.height);
			img.pixel_mat = NULL;
			
		}
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
	if(img->height == 0) {
		printf("No image loaded\n");
		return;
	}
	if (is_ascii) {
		FILE *out = fopen(filename, "wt");

		if (!out) {
			printf("Failed to save %s\n", filename);
			return;
		}
		if (img->type[1] == '4' ||  img->type[1] == '5' ||
			img->type[1] == '6') {
			fprintf(out, "%c%c\n", 'P', img->type[1] - 3);
		}
		else {
			fprintf(out, "%s\n", img->type);
		}
		fprintf(out, "%d %d\n", img->width, img->height);
		fprintf(out, "%d\n", img->max_val);

		if(img->type[1] == '1' || img->type[1] == '2' || img->type[1] == '4' || img->type[1] == '5') {
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fprintf(out, "%d ", img->pixel_mat[i][j].r);
				}
				fprintf(out, "\n");
			}
		} else if(img->type[1] == '3' || img->type[1] == '6') {
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
		
		if (img->type[1] == '1') {
			fprintf(out, "%c%c\n", 'P', '4');
		} else if (img->type[1] == '2') {
			fprintf(out, "%c%c\n", 'P', '5');
		} else if (img->type[1] == '3') {
			fprintf(out, "%c%c\n", 'P', '6');
		} else {
			fprintf(out, "%s\n", img->type);
		}
		fprintf(out, "%d %d\n", img->width, img->height);
		fprintf(out, "%d\n", img->max_val);

		if(img->type[1] == '1' || img->type[1] == '2' || img->type[1] == '4' || img->type[1] == '5') {
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fwrite(&img->pixel_mat[i][j].r, sizeof(unsigned char), 1, out);
				}
			}
		} else if(img->type[1] == '3' || img->type[1] == '6') {
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

void set_selection_all(image_t *img, selection_t *selection)
{
	selection->x1 = 0;
	selection->y1 = 0;
	selection->x2 = img->width;
	selection->y2 = img->height;
}

void handle_select(image_t *img, selection_t *selection, char *argument) {
	if (img->height == 0) {
		printf("No image loaded\n");
	} else {
		int x1, y1, x2, y2;
		if (strstr(argument, "ALL")) {
			set_selection_all(img, selection);
			printf("Selected ALL\n");
		} else {
			if (sscanf(argument, "%*s %d %d %d %d", &x1, &y1, &x2, &y2) != 4) {
				printf("Invalid command\n");
			} else {
				selection_t buffer = {0};
				buffer.x1 = (x1<x2) ? x1 : x2;
				buffer.y1 = (y1<y2) ? y1 : y2;
				buffer.x2 = (x2>x1) ? x2 : x1;
				buffer.y2 = (y2>y1) ? y2 : y1;
				if (buffer.x1 < 0 || buffer.x1 >= img->width ||
					buffer.x2 < 0 || buffer.x2 > img->width ||
					buffer.y1 < 0 || buffer.y1 >= img->height ||
					buffer.y2 < 0 || buffer.y2 > img->height ||
					(x1 == x2 && y1 == y2)) {
					printf("Invalid set of coordinates\n");
					return;
				} else {
					selection->x1 = (x1 < x2) ? x1 : x2;	
					selection->y1 = (y1 < y2) ? y1 : y2;
					selection->x2 = (x2 > x1) ? x2 : x1;
					selection->y2 = (y2 > y1) ? y2 : y1;
					printf("Selected %d %d %d %d\n", selection->x1, selection->y1, selection->x2, selection->y2);
				}
			}
			
		}
	}
}

bool is_selection_square(selection_t *selection)
{
	if (selection->x2 - selection->x1 != selection->y2 - selection->y1) {
		return false;
	}
	return true;
}
bool is_selection_all(image_t *img,selection_t *selection)
{
	if (selection->x1 == 0 && selection->y1 == 0 &&
		selection->x2 == img->width && selection->y2 == img->height) {
		return true;
	}
	return false;
}

void rotate(image_t *img, selection_t *selection, int angle)
{
    pixel_t **new_mat;

    // Ensure the angle is within the range [-360, 360]
    angle = angle % 360;

    // Determine new dimensions for allocation based on the angle
    if (is_selection_all(img, selection) && 
       (angle == 90 || angle == -270 || angle == 270 || angle == -90)) {
        new_mat = alloc_px_mat(img->width, img->height);
    } else {
        new_mat = alloc_px_mat(img->height, img->width);
    }

    // Handle rotation cases
    if (is_selection_all(img, selection)) {
        if (angle == 90 || angle == -270) {
            for (int i = 0; i < img->height; i++) {
                for (int j = 0; j < img->width; j++) {
                    new_mat[j][img->height - i - 1] = img->pixel_mat[i][j];
                }
            }
        } else if (angle == 180 || angle == -180) {
            for (int i = 0; i < img->height; i++) {
                for (int j = 0; j < img->width; j++) {
                    new_mat[img->height - i - 1][img->width - j - 1] = img->pixel_mat[i][j];
                }
            }
        } else if (angle == 270 || angle == -90) {
            for (int i = 0; i < img->height; i++) {
                for (int j = 0; j < img->width; j++) {
                    new_mat[img->width - j - 1][i] = img->pixel_mat[i][j];
                }
            }
        } else {
            // Copy original image if angle is 0 or unsupported
            for (int i = 0; i < img->height; i++) {
                for (int j = 0; j < img->width; j++) {
                    new_mat[i][j] = img->pixel_mat[i][j];
                }
            }
        }
    } else {
        // Handle rotation for a selected region
        for (int i = selection->y1; i < selection->y2; i++) {
            for (int j = selection->x1; j < selection->x2; j++) {
                if (angle == 90 || angle == -270) {
                    new_mat[j - selection->x1][selection->y2 - i - 1] = img->pixel_mat[i][j];
                } else if (angle == 180 || angle == -180) {
                    new_mat[selection->y2 - i - 1][selection->x2 - j - 1] = img->pixel_mat[i][j];
                } else if (angle == 270 || angle == -90) {
                    new_mat[selection->x2 - j - 1][i - selection->y1] = img->pixel_mat[i][j];
                } else {
                    new_mat[i - selection->y1][j - selection->x1] = img->pixel_mat[i][j];
                }
            }
        }
    }
	
    // Free the old pixel matrix and assign the new one
    if(is_selection_all(img, selection)) {
		free_px_mat(img->pixel_mat, img->height);
    	img->pixel_mat = new_mat;
		if (angle == 90 || angle == -270 || angle == 270 || angle == -90) {
       		int temp = img->width;
       		img->width = img->height;
       		img->height = temp;
    	}
		set_selection_all(img, selection);
	} else {
		for(int i = selection->y1; i < selection->y2; i++) {
			for(int j = selection->x1; j < selection->x2; j++) {
				img->pixel_mat[i][j] = new_mat[i - selection->y1][j - selection->x1];
			}
		}
		free_px_mat(new_mat, img->height);
	}
   
        
}

void crop(image_t *img, selection_t *selection)
{
	// Verify dimensions
	if (selection->x1 >= selection->x2 || selection->y1 >= selection->y2 ||
		selection->x1 < 0 || selection->y1 < 0 ||
		selection->x2 > img->width || selection->y2 > img->height) {
		return;
	}

	int new_height = selection->y2 - selection->y1;
	int new_width = selection->x2 - selection->x1;

	pixel_t **new_mat = alloc_px_mat(new_height, new_width);
	if (!new_mat)
		return;

	// Copy selected region to new matrix
	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			new_mat[i][j] = img->pixel_mat[i + selection->y1][j + selection->x1];
		}
	}

	// Free old matrix and update image properties
	free_px_mat(img->pixel_mat, img->height);
	img->height = new_height;
	img->width = new_width;
	img->pixel_mat = new_mat;
	
	set_selection_all(img, selection);
}

void histogram(image_t *img, selection_t *selection, int max_stars, int nr_of_bins)
{
	if (img->type[1] == '3' || img->type[1] == '6') {
		printf("Black and white image needed\n");
		return;
	}
	int freq[256] = {0};
	for(int i = selection->y1; i < selection->y2; i++) {
		for(int j = selection->x1; j < selection->x2; j++) {
			freq[img->pixel_mat[i][j].r]++;
		}
	}
	int new_freq[256] = {0}, maxfreq = 0;
	int steps = 256 / nr_of_bins;
	for (int i = 0; i < nr_of_bins; i++) {
		for(int j = 0; j < steps; j++) {
			new_freq[i] += freq[i * steps + j];
		}
		if (new_freq[i] > maxfreq) {
			maxfreq = new_freq[i];
		}
	}
	for (int i = 0; i < nr_of_bins; i++) {
		int nr_stars = (new_freq[i] * max_stars) / maxfreq;
		printf("%d\t|\t", nr_stars);
		for (int j = 0; j < nr_stars; j++) {
			printf("*");
		}
		printf("\n");
	}
}

void equalize(image_t *img)
{
    if(img->height == 0) {
        printf("No image loaded\n");
        img->pixel_mat = NULL;
        return;
    }
    if (img->type[1] == '3' || img->type[1] == '6') {
        printf("Black and white image needed\n");
        return;
    }

    // Calculate histogram
    int freq[256] = {0};
    int total_pixels = img->height * img->width;
    
    for(int i = 0; i < img->height; i++) {
        for(int j = 0; j < img->width; j++) {
            freq[img->pixel_mat[i][j].r]++;
        }
    }

    // Calculate cumulative distribution
    int cumulative[256] = {0};
    cumulative[0] = freq[0];
    for(int i = 1; i < 256; i++) {
        cumulative[i] = cumulative[i-1] + freq[i];
    }

    // Apply transformation
    for(int i = 0; i < img->height; i++) {
        for(int j = 0; j < img->width; j++) {
            int old_value = img->pixel_mat[i][j].r;
            // Scale the value using the cumulative distribution
            int new_value = (int)round((double)cumulative[old_value] * 255 / total_pixels);
            img->pixel_mat[i][j].r = (unsigned char)clamp(new_value);
            img->pixel_mat[i][j].g = img->pixel_mat[i][j].r;
            img->pixel_mat[i][j].b = img->pixel_mat[i][j].r;
        }
    }
    
    printf("Equalize done\n");
    return;
}

int clamp(int value)
{
	if (value < 0) {
		return 0;
	}
	if (value > 255) {
		return 255;
	}
	return value;
}

void apply_edge(image_t *img, selection_t *selection)
{
	pixel_t **new_mat = alloc_px_mat(img->height, img->width);
	if (!new_mat)
		return;
	int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int dv[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
	for (int i = selection->y1; i < selection->y2; i++) {
		for (int j = selection->x1; j < selection->x2; j++) {
			bool is_edge = false;
			double sum_r = 0, sum_g = 0, sum_b = 0;
			for (int k = 0; k < 9; k++) {
				int ni = i + di[k];
				int nj = j + dj[k];
				if (ni < 0 || ni >= img->height || nj < 0 || nj >= img->width) {
					is_edge = true;
					break;
				} else {
					sum_r += img->pixel_mat[ni][nj].r * dv[k];
					sum_g += img->pixel_mat[ni][nj].g * dv[k];
					sum_b += img->pixel_mat[ni][nj].b * dv[k];
				}
			}
			if(!is_edge) {
				new_mat[i][j].r = clamp((int)round(sum_r));
				new_mat[i][j].g = clamp((int)round(sum_g));
				new_mat[i][j].b = clamp((int)round(sum_b));
			} else {
				new_mat[i][j].r = img->pixel_mat[i][j].r;
				new_mat[i][j].g = img->pixel_mat[i][j].g;
				new_mat[i][j].b = img->pixel_mat[i][j].b;
			}
		}
	}
	for (int i = selection->y1; i < selection->y2; i++) {
		for (int j = selection->x1; j < selection->x2; j++) {
			img->pixel_mat[i][j] = new_mat[i][j];
		}
	}
	free_px_mat(new_mat, img->height);
}

void apply_sharpen(image_t *img, selection_t *selection)
{
	pixel_t **new_mat = alloc_px_mat(img->height, img->width);
	if (!new_mat)
		return;
	int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int dv[9] = {0, -1 , 0, -1, 5, -1, 0, -1, 0};
	for (int i = selection->y1; i < selection->y2; i++) {
		for (int j = selection->x1; j < selection->x2; j++) {
			bool is_edge = false;
			double sum_r = 0, sum_g = 0, sum_b = 0;
			for (int k = 0; k < 9; k++) {
				int ni = i + di[k];
				int nj = j + dj[k];
				if (ni < 0 || ni >= img->height || nj < 0 || nj >= img->width) {
					is_edge = true;
					break;
				} else {
					sum_r += img->pixel_mat[ni][nj].r * dv[k];
					sum_g += img->pixel_mat[ni][nj].g * dv[k];
					sum_b += img->pixel_mat[ni][nj].b * dv[k];
				}
			}
			if(!is_edge) {
				new_mat[i][j].r = clamp((int)round(sum_r));
				new_mat[i][j].g = clamp((int)round(sum_g));
				new_mat[i][j].b = clamp((int)round(sum_b));
			} else {
				new_mat[i][j].r = img->pixel_mat[i][j].r;
				new_mat[i][j].g = img->pixel_mat[i][j].g;
				new_mat[i][j].b = img->pixel_mat[i][j].b;
			}
		}
	}
	for (int i = selection->y1; i < selection->y2; i++) {
		for (int j = selection->x1; j < selection->x2; j++) {
			img->pixel_mat[i][j] = new_mat[i][j];
		}
	}
	free_px_mat(new_mat, img->height);
}

void apply_box_blur(image_t *img, selection_t *selection)
{
	pixel_t **new_mat = alloc_px_mat(img->height, img->width);
	if (!new_mat)
		return;
	int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int dv[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	for (int i = selection->y1; i < selection->y2; i++) {
		for (int j = selection->x1; j < selection->x2; j++) {
			bool is_edge = false;
			double sum_r = 0, sum_g = 0, sum_b = 0;
			for (int k = 0; k < 9; k++) {
				int ni = i + di[k];
				int nj = j + dj[k];
				if (ni < 0 || ni >= img->height || nj < 0 || nj >= img->width) {
					is_edge = true;
					break;
				} else {
					sum_r += img->pixel_mat[ni][nj].r * dv[k];
					sum_g += img->pixel_mat[ni][nj].g * dv[k];
					sum_b += img->pixel_mat[ni][nj].b * dv[k];
				}
			}
			if (!is_edge) {
				new_mat[i][j].r = clamp((int)round(sum_r / 9));
				new_mat[i][j].g = clamp((int)round(sum_g / 9));
				new_mat[i][j].b = clamp((int)round(sum_b / 9));
			} else {
				new_mat[i][j].r = img->pixel_mat[i][j].r;
				new_mat[i][j].g = img->pixel_mat[i][j].g;
				new_mat[i][j].b = img->pixel_mat[i][j].b;
			}
		}
	}
	for (int i = selection->y1; i < selection->y2; i++) {
		for (int j = selection->x1; j < selection->x2; j++) {
			img->pixel_mat[i][j] = new_mat[i][j];
		}
	}
	free_px_mat(new_mat, img->height);
}

void apply_gaussian_blur(image_t *img, selection_t *selection)
{
	pixel_t **new_mat = alloc_px_mat(selection->y2 - selection->y1, selection->x2 - selection->x1);
	if (!new_mat)
	    return;

	int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
	int dv[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

	for (int i = selection->y1; i < selection->y2; i++) {
	    for (int j = selection->x1; j < selection->x2; j++) {
	        bool is_edge = false;
	        double sum_r = 0, sum_g = 0, sum_b = 0;
	        for (int k = 0; k < 9; k++) {
	            int ni = i + di[k];
	            int nj = j + dj[k];
	            if (ni < 0 || ni >= img->height || nj < 0 || nj >= img->width) {
	                is_edge = true;
	                break;
	            } else {
	                sum_r += img->pixel_mat[ni][nj].r * dv[k];
	                sum_g += img->pixel_mat[ni][nj].g * dv[k];
	                sum_b += img->pixel_mat[ni][nj].b * dv[k];
	            }
	        }
	        if (!is_edge) {
	            new_mat[i - selection->y1][j - selection->x1].r = clamp((int)round(sum_r / 16));
	            new_mat[i - selection->y1][j - selection->x1].g = clamp((int)round(sum_g / 16));
	            new_mat[i - selection->y1][j - selection->x1].b = clamp((int)round(sum_b / 16));
	        } else {
	            new_mat[i - selection->y1][j - selection->x1].r = img->pixel_mat[i][j].r;
	            new_mat[i - selection->y1][j - selection->x1].g = img->pixel_mat[i][j].g;
	            new_mat[i - selection->y1][j - selection->x1].b = img->pixel_mat[i][j].b;
	        }
	    }
	}

	for (int i = selection->y1; i < selection->y2; i++) {
	    for (int j = selection->x1; j < selection->x2; j++) {
	        img->pixel_mat[i][j] = new_mat[i - selection->y1][j - selection->x1];
	    }
	}

	free_px_mat(new_mat, selection->y2 - selection->y1);
}

void apply_filter(image_t *img, selection_t *selection, char *argument)
{
	if(img->height == 0) {
		printf("No image loaded\n");
		return;
	}

	char filter[256];
	if (sscanf(argument, "%*s %s", filter) != 1) {
		printf("Invalid command\n");
		return;
	}
	
	if (strcmp(filter, "EDGE") == 0) {
		if(img->type[1] != '3' && img->type[1] != '6') {
			printf("Easy, Charlie Chaplin\n");
			return;
		} else {
			apply_edge(img, selection);
		}
	} else if (strcmp(filter, "SHARPEN") == 0) {
		if(img->type[1] != '3' && img->type[1] != '6') {
			printf("Easy, Charlie Chaplin\n");
			return;
		} else {
			apply_sharpen(img, selection);
		}
	} else if (strcmp(filter, "BLUR") == 0) {
		if(img->type[1] != '3' && img->type[1] != '6') {
			printf("Easy, Charlie Chaplin\n");
			return;
		} else {
			apply_box_blur(img, selection);
		}
	} else if (strcmp(filter, "GAUSSIAN_BLUR") == 0) {
		if(img->type[1] != '3' && img->type[1] != '6') {
			printf("Easy, Charlie Chaplin\n");
			return;
		} else {
			apply_gaussian_blur(img, selection);
		}
	} else {
		printf("APPLY parameter invalid\n");
		return;
	}

	printf("APPLY %s done\n", filter);
}