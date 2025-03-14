# 311CA_MihutMatei_Tema3

## Overview

This project is an image editor that supports the following operations on images: loading, saving, rotating, cropping, applying filters, equalizing grayscale images, and generating histograms. The editor supports plain and binary Netpbm images in black and white, grayscale, and color.

## Features

- Load and save images in PGM, PPM, and BW formats (both plain and binary).
- Select regions of the image for operations.
- Rotate the selected region by multiples of 90 degrees.
- Crop the image to the selected region.
- Apply various filters to the selected region: edge detection, sharpening, box blur, and Gaussian blur.
- Generate histograms for the selected region.
- Equalization of grayscale images

## Code Insight

### Compartmentalization

The code is split up into three files:

- `image_editor.c`: This is the main file that contains the `main` function and handles user commands. It processes input commands and calls the appropriate functions to perform operations on the image.
- `utils.c`: This file contains utility functions for image processing, such as loading, saving, rotating, cropping, applying filters, equalizing, and generating histograms. It also includes memory management functions for allocating and freeing the pixel matrix.
- `image_editor.h`: This header file contains the declarations of the structs (`pixel_t`, `image_t`, `selection_t`) and function prototypes used in the project. It provides the necessary interface for the functions implemented in `utils.c` to be used in `image_editor.c`.

### The Main Way of Handling Information

The information regarding pixels, images, and the selection zone upon which the code operates is held in three different structs:

- `pixel_t`: has three `unsigned char` variables: `r`, `g`, `b` (`unsigned char` so that each value occupies 1 byte and the writing and reading from binary files is handled correctly).
- `image_t`: has three `int` variables: `width`, `height`, `max_val`, a statically allocated null-terminated string `type`, and a 2D dynamically allocated `pixel_t` array `pixel_mat`.
- `selection_t`: has four `int` variables: `x1`, `y1`, `x2`, `y2`, representing the coordinates of the selection zone.

### How Loading Works

To load an image, the program first checks if there is another image already loaded. If an image is already loaded, it frees the `pixel_mat` of the current image before loading the new one.

The program then reads the image type, width, height, and `max_val` from the file. Based on the image type, it calls different auxiliary functions to load the image appropriately.

If the image type is not supported or there is an error reading the file, an error message is printed, and the loading process is aborted.

After successfully loading the new image, a success message is printed, and the selection zone is set to the whole image.

### How Saving Works

To save an image, the program first checks if an image is loaded. If no image is loaded, it prints an error message. If an image is loaded, it opens the specified file in write mode (either text or binary, depending on the format).

The program writes the image type, width, height, and `max_val` to the file. Then, it writes the pixel data to the file. For ASCII formats, the pixel values are written as space-separated integers. For binary formats, the pixel values are written as bytes.

**Important**: The type written in the file is modified accordingly so that binary files have the correct type, even if the image loaded in memory was originally plain and vice versa.

After writing the pixel data, the file is closed, and a success message is printed.

### How Selection Works

To select a region of the image, the program processes the `SELECT` command followed by the coordinates of the selection zone. The coordinates are provided as four integers: `x1`, `y1`, `x2`, `y2`, that are processed into the `selection_t` struct to represent the top-left and bottom-right corners of the selection zone.

If the `SELECT ALL` command is used, the entire image is selected. The program sets the selection coordinates to cover the whole image.

The program validates the provided coordinates to ensure they are within the bounds of the image and that the selection is not a single point. If the coordinates are valid, the selection is updated, and a success message is printed. If the coordinates are invalid, an error message is displayed.

### How Rotation Works

To rotate a region of the image, the program first processes the `ROTATE` command followed by the angle of rotation. The angle must be a multiple of 90 degrees. The program validates the angle to ensure it is supported.

If the angle is valid, the program checks if the selection is square or if the entire image is selected. If the selection is not square and not the entire image, an error message is displayed, and the rotation is not performed.

If the selection is valid, the program rotates the selected region by the specified angle. The rotation is performed by creating a new pixel matrix and copying the pixels from the original matrix to the new matrix in the rotated positions.

After the rotation is complete, the original pixel matrix is replaced with the new matrix if the selection was the entire image. Otherwise, the rotated pixels from the new matrix are copied back into the original matrix, and the new matrix is freed.

### How Cropping Works

To crop an image, the program processes the `CROP` command. The program first checks if an image is loaded. If no image is loaded, it prints an error message.

If an image is loaded, the program validates the current selection coordinates to ensure they are within the bounds of the image and that the selection is not a single point. If the coordinates are invalid, an error message is displayed, and the cropping is not performed.

If the coordinates are valid, the program creates a new pixel matrix with dimensions matching the selection. It then copies the pixels from the selected region of the original matrix to the new matrix.

After copying the pixels, the original pixel matrix is freed, and the image dimensions are updated to match the new matrix. The new matrix becomes the current pixel matrix of the image.

Finally, the selection zone is updated to cover the entire newly cropped image, and a success message is printed.

### How Apply Works

To apply a filter to a region of the image, the program processes the `APPLY` command followed by the name of the filter. The program validates the filter name to ensure it is supported.

If the filter name is valid, the program applies the specified filter to the selected region. The filters are implemented using convolution with predefined kernels.

Each filter uses three vectors: `di`, `dj`, and `dv`. For each pixel in the original matrix, we go through all its neighbors using `di` and `dj`, and add to the sum of each color channel the RGB values of that pixel multiplied by the corresponding `dv` member. This is the convolution implementation.

#### Edge Detection

The edge detection filter highlights the edges in the image. It uses the following kernel:

```c
int dv[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
```

#### Sharpen

The sharpen filter enhances the edges and details in the image. It uses the following kernel:

```c
int dv[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
```

#### Box Blur

The box blur filter smooths the image by averaging the pixel values in the neighborhood. It uses the following kernel:

```c
int dv[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
```

and divides the sum by 9.

#### Gaussian Blur

The Gaussian blur filter smooths the image using the following kernel:

```c
int dv[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
```

### How Histogram Generation Works

To generate a histogram for a region of the image, the program processes the `HISTOGRAM` command followed by the maximum number of stars (`mx_stars`) and the number of bins (`nr_bins`). The program validates the parameters to ensure they are within acceptable ranges.

If the parameters are valid, the program calculates the histogram for the selected region. The histogram generation process involves the following steps:

1. **Initialize the Histogram**: Create an array to store the frequency of pixel values for each bin. The size of the array is equal to the maximum value of the pixels, in our case 256.
2. **Calculate Bin Width**: Determine the width of each bin by dividing the range of pixel values (0 to 255) by the number of bins (`nr_bins`).
3. **Count Pixel Frequencies**: Iterate over each pixel in the selected region and determine the corresponding bin for each pixel value. Increment the frequency count for the appropriate bin.
4. **Normalize the Histogram**: Normalize the histogram by dividing each bin's frequency by the total number of pixels in the selected region. This ensures that the histogram represents the relative frequency of pixel values.
5. **Scale the Histogram**: Scale the histogram to fit within the specified maximum number of stars (`max_stars`). This involves finding the bin with the highest frequency and scaling all bins relative to this maximum frequency.
6. **Print the Histogram**: Print the histogram as a series of lines, with each line representing a bin. The number of stars on each line corresponds to the scaled frequency of the bin.

### How Equalization Works

To equalize the histogram of an image, the program processes the `EQUALIZE` command. The equalization process involves the following steps:

1. **Check Image Type**: Ensure that the image is a grayscale image (PGM format). If the image is not grayscale, an error message is displayed, and the equalization is not performed.
2. **Calculate Histogram**: Create an array to store the frequency of pixel values (0 to 255). Iterate over each pixel in the image and increment the frequency count for the corresponding pixel value.
3. **Calculate Cumulative Distribution Function (CDF)**: Create an array to store the cumulative frequency of pixel values. The CDF is calculated by summing the frequencies of all pixel values up to the current value. Normalize the CDF by dividing each value by the total number of pixels in the image.
4. **Map Pixel Values**: Create a mapping of old pixel values to new pixel values using the CDF. The new value for each pixel is calculated by multiplying the CDF value by the maximum pixel value (255) and rounding to the nearest integer.
5. **Apply Mapping**: Iterate over each pixel in the image and replace the old pixel value with the new value from the mapping.
6. **Update Image**: Update the image with the new pixel values and print a success message.

## Usage

### Build

To build the project, run the following command:

```sh
make build
```

### Run

To run the image editor, execute the following command:

```sh
./image_editor
```

### Commands (Usage)

- `LOAD <filename>`: Load an image from the specified file.
- `SAVE <filename> [ascii]`: Save the image to the specified file. Optionally, save in ASCII format.
- `SELECT <x1> <y1> <x2> <y2>`: Select a rectangular region of the image.
- `SELECT ALL`: Select the entire image.
- `ROTATE <angle>`: Rotate the selected region by the specified angle (90, 180, or 270 degrees).
- `CROP`: Crop the image to the selected region.
- `APPLY <filter>`: Apply the specified filter to the selected region. Supported filters: `EDGE`, `SHARPEN`, `BLUR`, `GAUSSIAN_BLUR`.
- `HISTOGRAM <max_stars> <nr_of_bins>`: Generate a histogram for the selected region.
- `EQUALIZE`: Equalize the histogram of the image.
- `EXIT`: Exit the image editor.

## Example

Here is an example of how to use the image editor:

```sh
./image_editor
LOAD example.pgm
SELECT 0 0 100 100
ROTATE 90
APPLY EDGE
SAVE output.pgm
EXIT
```

## Clean

To clean the build files, run the following command:

```sh
make clean
```

## Pack

To create a zip archive of the project, run the following command:

```sh
make pack
```
