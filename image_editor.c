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

	char command[256];
	scanf("%s", command);
	while(strcmp(command, "EXIT") != 0) {
		if (strcmp(command, "LOAD") == 0) {
			char filename[256];
			scanf("%s", filename);
			if (img.pixel_mat) {
				free_px_mat(img.pixel_mat, img.width);
				img.pixel_mat = NULL;
			}
			img = load(filename);
		} else if (strcmp(command, "SELLECT") == 0) {
			
		} else if (strcmp(command, "ROTATE") == 0) {
			
		} else if (strcmp(command, "EQUALIZE") == 0) {
			
		} else if (strcmp(command, "CROP") == 0) {
			
		} else if (strcmp(command, "APPLY") == 0) {
			
		} else if (strcmp(command, "HISTOGRAM") == 0) {
			
		} else if (strcmp(command, "SAVE") == 0) {
			char save_file_name[256];
			scanf("%s", save_file_name);
			save(&img, save_file_name, false);
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