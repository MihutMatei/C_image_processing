//311CA_MihutMatei_Tema3
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "image_editor.h"

int main(void)
{
	image_t img = {0};
	selection_t selection = {0};
	char command[256], buffer[256];

	fgets(buffer, 256, stdin);
	sscanf(buffer, "%s", command);

	while (strcmp(command, "EXIT") != 0) {
		
		if (strcmp(command, "EXIT") == 0) {
			break;
		} else if (strcmp(command, "LOAD") == 0) {
			char filename[256];
			sscanf(buffer, "%*s %s", filename);
			if (img.pixel_mat) {
				free_px_mat(img.pixel_mat, img.height);
				img.pixel_mat = NULL;
			}
			img = load(filename);
			set_selection_all(&img, &selection);
		} else if (strcmp(command, "SELECT") == 0) {
			handle_select(&img, &selection, buffer);
		} else if (strcmp(command, "ROTATE") == 0) {
			if (img.height == 0) {
				printf("No image loaded\n");
			} else {
				if (!is_selection_square(&selection) &&
					!is_selection_all(&img, &selection)) {
					printf("The selection must be square\n");
				} else {
					int angle;
					sscanf(buffer, "%*s %d", &angle);
					if (angle % 90 != 0) {
						printf("Unsupported rotation angle\n");
					} else {
						rotate(&img, &selection, angle);
						printf("Rotated %d\n", angle);
					}
				}
			}
		} else if (strcmp(command, "EQUALIZE") == 0) {
			equalize(&img, &selection);
		} else if (strcmp(command, "CROP") == 0) {
			if (img.height == 0) {
				printf("No image loaded\n");
			} else {
				crop(&img, &selection);
				printf("Image cropped\n");
			}
		} else if (strcmp(command, "APPLY") == 0) {
			apply_filter(&img, &selection, buffer);
		} else if (strcmp(command, "HISTOGRAM") == 0) {
			if (img.height == 0) {
				printf("No image loaded\n");
			} else {
				int max_stars, nr_of_bins;
				if (sscanf(buffer, "%*s %d %d", &max_stars, &nr_of_bins) < 2) {
					printf("Invalid command\n");
				} else if (nr_of_bins > 256) {
					printf("Invalid set of parameters\n");
				} else {
					int trash1;
					sscanf(buffer, "%*s %*d %*d %d", &trash1);
					if (trash1 != 0) {
						printf("Invalid command\n");
					} else {
						histogram(&img, &selection, max_stars, nr_of_bins);
					}
				}
			}
		} else if (strcmp(command, "SAVE") == 0) {
			char save_file_name[256], is_ascii[256];
			sscanf(buffer, "%*s %s %s", save_file_name, is_ascii);
			if (strcmp(is_ascii, "ascii") == 0) {
				save(&img, save_file_name, true);
			} else {
				save(&img, save_file_name, false);
			}
		} else {
			printf("Invalid command\n");
		}
		fgets(buffer, 256, stdin);
		sscanf(buffer, "%s", command);
	}

	if (img.pixel_mat) {
		free_px_mat(img.pixel_mat, img.height);
		img.pixel_mat = NULL;
	} else {
		printf("No image loaded\n");
	}

	return 0;
}