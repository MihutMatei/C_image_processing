//311CA_MihutMatei_Tema3
#ifndef MYHEADER_H
#define MYHEADER_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief Structure representing a pixel with RGB values.
 */
typedef struct {
	unsigned char r; /**< Red component */
	unsigned char g; /**< Green component */
	unsigned char b; /**< Blue component */
} pixel_t;

/**
 * @brief Structure representing an image.
 */
typedef struct {
	char type[4]; /**< Image type (e.g., P3, P6) */
	int width; /**< Image width */
	int height; /**< Image height */
	int max_val; /**< Maximum pixel value */
	pixel_t **pixel_mat; /**< 2D array of pixels (dynamically allocated)*/
} image_t;

/**
 * @brief Structure representing a selection within an image.
 */
typedef struct {
	int x1, y1, x2, y2; /**< Coordinates of the selection */
} selection_t;

/**
 * @brief Allocates memory for a 2D array of pixels.
 *
 * @param size1 Number of rows.
 * @param size2 Number of columns.
 * @return Pointer to the allocated 2D array of pixels.
 */
pixel_t **alloc_px_mat(int size1, int size2);

/**
 * @brief Frees memory allocated for a 2D array of pixels.
 *
 * @param mat Pointer to the 2D array of pixels.
 * @param size Number of rows.
 */
void free_px_mat(pixel_t **mat, int size);

/**
 * @brief Loads an image from a file.
 *
 * @param filename Name of the file to load the image from.
 * @return Loaded image.
 */
image_t load(char *filename);

/**
 * @brief Saves an image to a file.
 *
 * @param img Pointer to the image to save.
 * @param filename Name of the file to save the image to.
 * @param is_ascii Whether to save the image in ASCII format.
 */
void save(image_t *img, char *filename, bool is_ascii);

/**
 * @brief Handles the selection command.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 * @param argument Command argument.
 */
void handle_select(image_t *img, selection_t *selection, char *argument);

/**
 * @brief Sets the selection to the entire image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 */
void set_selection_all(image_t *img, selection_t *selection);

/**
 * @brief Checks if the selection is square.
 *
 * @param selection Pointer to the selection structure.
 * @return True if the selection is square, false otherwise.
 */
bool is_selection_square(selection_t *selection);

/**
 * @brief Checks if the selection covers the entire image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 * @return True if the selection covers the entire image, false otherwise.
 */
bool is_selection_all(image_t *img, selection_t *selection);

/**
 * @brief Rotates the selected region of the image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 * @param angle Rotation angle in degrees.
 */
void rotate(image_t *img, selection_t *selection, int angle);

/**
 * @brief Handles the rotate command.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 * @param buffer Command buffer.
 */
void handle_rotate(image_t *img, selection_t *selection, char *buffer);

/**
 * @brief Crops the image to the selected region.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 */
void crop(image_t *img, selection_t *selection);

/**
 * @brief Generates a histogram of the selected region of the image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 * @param mx_stars Maximum number of stars in the histogram.
 * @param nr_bins Number of bins in the histogram.
 */
void histogram(image_t *img, selection_t *selection, int mx_stars, int nr_bins);

/**
 * @brief Handles the histogram command.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 * @param buffer Command buffer.
 */
void handle_histogram(image_t *img, selection_t *selection, char *buffer);

/**
 * @brief Equalizes the histogram of the image.
 *
 * @param img Pointer to the image.
 */
void equalize(image_t *img);

/**
 * @brief Applies a filter to the selected region of the image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 * @param argument Command argument.
 */
void apply_filter(image_t *img, selection_t *selection, char *argument);

/**
 * @brief Applies an edge detection filter to the selected region of the image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 */
void apply_edge(image_t *img, selection_t *selection);

/**
 * @brief Applies a sharpen filter to the selected region of the image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 */
void apply_sharpen(image_t *img, selection_t *selection);

/**
 * @brief Applies a box blur filter to the selected region of the image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 */
void apply_box_blur(image_t *img, selection_t *selection);

/**
 * @brief Applies a Gaussian blur filter to the selected region of the image.
 *
 * @param img Pointer to the image.
 * @param selection Pointer to the selection structure.
 */
void apply_gaussian_blur(image_t *img, selection_t *selection);

/**
 * @brief Loads a plain PGM image from a file.
 *
 * @param in File pointer.
 * @param img Pointer to the image structure.
 * @return Loaded image.
 */
image_t load_pgm(FILE *in, image_t *img);

/**
 * @brief Loads a plain PPM image from a file.
 *
 * @param in File pointer.
 * @param img Pointer to the image structure.
 * @return Loaded image.
 */
image_t load_ppm(FILE *in, image_t *img);

/**
 * @brief Loads a plain Black and White image from a file.
 *
 * @param in File pointer.
 * @param img Pointer to the image structure.
 * @return Loaded image.
 */
image_t load_bw(FILE *in, image_t *img);

/**
 * @brief Loads a binary PGM image from a file.
 *
 * @param in File pointer.
 * @param img Pointer to the image structure.
 * @return Loaded image.
 */
image_t load_binary_pgm(FILE *in, image_t *img);

/**
 * @brief Loads a binary PPM image from a file.
 *
 * @param in File pointer.
 * @param img Pointer to the image structure.
 * @return Loaded image.
 */
image_t load_binary_ppm(FILE *in, image_t *img);

/**
 * @brief Loads a binary Black and White image from a file.
 *
 * @param in File pointer.
 * @param img Pointer to the image structure.
 * @return Loaded image.
 */
image_t load_binary_bw(FILE *in, image_t *img);

/**
 * @brief Clamps a value to the range [0, 255].
 *
 * @param value Integer to clamp.
 * @return Clamped value.
 */
int clamp(int value);

#endif
