//311CA_MihutMatei_Tema3
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "image_editor.h"

int main(void)
{
	image_t img = {0};
	selection_t selection = {0};

	char command[256];
	scanf("%s", command);
	while(strcmp(command, "EXIT") != 0) {
		if (strcmp(command, "LOAD") == 0) {
			char filename[256];
			scanf("%s", filename);
			if (img.pixel_mat) {
				free_px_mat(img.pixel_mat, img.height);
				img.pixel_mat = NULL;
			}
			img = load(filename);
			set_selection_all(&img, &selection);

		} else if (strcmp(command, "SELECT") == 0) {
			
			handle_select(&img, &selection);

		} else if (strcmp(command, "ROTATE") == 0) {

			if (img.height == 0) {
				printf("No image loaded\n");
			} else {
				if (!is_selection_square(&selection) &&
					!is_selection_all(&img, &selection)) {
					printf("The selection must be square\n");
				} else {
					int angle;
					scanf("%d", &angle);
					if (angle % 90 != 0) {
						printf("Unsupported rotation angle\n");
					} else {
						rotate(&img, &selection , angle);
						printf("Rotated %d\n", angle);
					}
				}
			}

		} else if (strcmp(command, "EQUALIZE") == 0) {
			
		} else if (strcmp(command, "CROP") == 0) {
			
		} else if (strcmp(command, "APPLY") == 0) {
			
		} else if (strcmp(command, "HISTOGRAM") == 0) {
			
		} else if (strcmp(command, "SAVE") == 0) {
			//TODO: implement ascii or no ascii
			char argument[256], save_file_name[256], is_ascii[256];
		
			fgets(argument, 256, stdin);
			sscanf(argument, "%s %s", save_file_name, is_ascii);

			if (strcmp(is_ascii, "ascii") == 0) {
				save(&img, save_file_name, true);
			} else {
				save(&img, save_file_name, false);
			}
			
		} else {
			printf("Invalid command\n");
		}
		scanf("%s", command);
	}
	if(img.height == 0) {
		printf("No image loaded\n");
	} else {
		//free everything
		free_px_mat(img.pixel_mat, img.height);
	}

	return 0;
}