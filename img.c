#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

void rotate(struct image* const img, enum side side) {

	size_t width = img->width;
	size_t height = img->height;
	struct pixel* new_matrix = malloc(sizeof(struct pixel)*width*height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			switch (side) {
			case 0: *(new_matrix + i*height + j) = *(img->data + j*width + (width - i - 1)); break;
			case 1: *(new_matrix + i*height + j) = *(img->data + (height - j - 1)*width + i); break;
			}
		}
	}
	img->width = height;
	img->height = width;
	free(img->data);
	img->data = new_matrix;
}
