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
	char command[256] = {0}; // Initialize command array
	char buffer[256] = {0};  // Initialize buffer array

	fgets(buffer, 256, stdin);
	if (sscanf(buffer, "%s", command) != 1) {
		printf("Invalid command\n");
		return 0;
	}

	while (strcmp(command, "EXIT") != 0) {

		if (strcmp(command, "EXIT") == 0) {
			break;
		} else if (strcmp(command, "LOAD") == 0) {
			char filename[256];
			if (sscanf(buffer, "%*s %s", filename) == 1) {
				if (img.pixel_mat) {
					free_px_mat(img.pixel_mat, img.height);
					img.pixel_mat = NULL;
				}
				img = load(filename);
				set_selection_all(&img, &selection);
			}
		} else if (strcmp(command, "SELECT") == 0) {
			handle_select(&img, &selection, buffer);
		} else if (strcmp(command, "ROTATE") == 0) {
			handle_rotate(&img, &selection, buffer);
		} else if (strcmp(command, "EQUALIZE") == 0) {
			equalize(&img);
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
			handle_histogram(&img, &selection, buffer);
		} else if (strcmp(command, "SAVE") == 0) {
			char save_file_name[256] = "", is_ascii[256] = "";
			if (sscanf(buffer, "%*s %s %s", save_file_name, is_ascii) > 0) {
				if (strcmp(is_ascii, "ascii") == 0) {
					save(&img, save_file_name, true);
				} else {
					save(&img, save_file_name, false);
				}
			}

		} else {
			printf("Invalid command\n");
		}
		fgets(buffer, 256, stdin);
		if (sscanf(buffer, "%s", command) == 0) {
			printf("Invalid command\n");
			break;
		}
	}

	if (img.pixel_mat) {
		free_px_mat(img.pixel_mat, img.height);
		img.pixel_mat = NULL;
	} else {
		printf("No image loaded\n");
	}

	return 0;
}
