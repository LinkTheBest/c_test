#include <stdio.h>
#include <stdlib.h>
#include "bmp_io.h"
#include "bmp_main.h"
#include "image_rotation.h"
#include "image_struct.h"

struct image rotate(struct image* const img, enum side const side) {

	size_t width = img->width;
	size_t height = img->height;
	struct pixel* new_matrix = malloc(sizeof(struct pixel)*width*height);
	for (size_t i = 0; i < width; i++) {
		for (size_t j = 0; j < height; j++) {
			switch (side) {
			case 0: *(new_matrix + i*height + j) = *(img->data + j*width + (width - i - 1)); break;
			case 1: *(new_matrix + i*height + j) = *(img->data + (height - j - 1)*width + i); break;
			}
		}
	}
	struct image new_img = {height, width, new_matrix};
	return new_img;
}
