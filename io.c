#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "error_printing.h"
#include "bmp_io.h"
#include "bmp_main.h"

void error_print(int64_t err) {
	switch (err) {
		case 1: printf(">> INVALID SIGNATURE <<\n"); break;
		case 2:	printf(">> INVALID RESERVED <<\n"); break;
		case 3:	printf(">> INVALID HEADER <<\n"); break;
		case 4: printf(">> INVALID OFFSET PIXELS <<\n"); break;
		case 5:	printf(">> FILE CORRUPTED <<\n"); break;
	}
}


enum read_status read_header(FILE* const file_path, struct bmp_header* const header) {
	fread(header, sizeof(struct bmp_header), 1, file_path);
	
	if (header->bfType != 0x4D42)
		return READ_INVALID_SIGNATURE;	
	 if(header -> biBitCount != 24)
		return READ_INVALID_HEADER;
	if(header->bOffBits != sizeof(struct bmp_header))
		return READ_INVALID_BITS;
	return READ_OK;
}

 enum read_status read_pixels(FILE* const file_path, struct bmp_header* const header, struct pixel* const data) {
	int64_t w = header->biWidth;
	int64_t h = header->biHeight;
	int64_t padding = (4 - (w * sizeof(struct pixel)) % 4) % 4;
	
	for (int64_t i = 0; i < h; i++) {
		int64_t kol = fread(data + i*w, sizeof(struct pixel), w, file_path);
		if (kol != w) {
			return 1;
		}
		fseek(file_path, padding, SEEK_CUR);
	}
	return READ_OK;
}

	enum read_status from_bmp(FILE* const file_path, struct image* const img) {
		struct bmp_header * header = malloc(sizeof(struct bmp_header));	
		enum read_status error = read_header(file_path, header);
		if (error) return error;
		int64_t height = header->biHeight;
		int64_t width = header->biWidth;
		int64_t off = header->bOffBits;
		fseek(file_path, off, SEEK_SET);
		img->data = malloc(height * width * sizeof(struct pixel));
		img->height = height;
		img->width = width;
		
		error = read_pixels(file_path, header, img->data);
		free(header);
		return error;
}

enum write_status to_bmp(FILE* const file_path, struct image const * img) {
    struct pixel* matrix = img->data;
	struct bmp_header header;

	int64_t w = img->width;
	int64_t h = img->height;
	int64_t padding = (4 - (w * sizeof(struct pixel)) % 4) % 4;
	int64_t i_size = (w * sizeof(struct pixel) + padding)*h;
	int64_t f_size = sizeof(struct bmp_header) + i_size;


	header.bfType = 0x4D42;
	header.bfileSize = f_size;
	header.bfReserved = 0;
	header.bOffBits = sizeof(struct bmp_header);
	header.biSize = 40;
	header.biWidth = w;
	header.biHeight = h;
	header.biPlanes = 1;
	header.biBitCount = 24;
	header.biCompression = 0;
	header.biSizeImage = h * (w * sizeof(struct pixel) + w % 4);
	header.biXPelsPerMeter = 0;
	header.biYPelsPerMeter = 0;
	header.biClrUsed = 0;
	header.biClrImportant = 0;


	if (fwrite(&header, 1, sizeof(header), file_path) != sizeof(header))
		return WRITE_ERROR;
		
	for (int64_t i = 0; i < h; i++) {
		fwrite(matrix + (i*w), sizeof(struct pixel), w, file_path);
		fwrite(&padding, 1, padding, file_path);
	}
	if (fclose(file_path) == EOF) 
		return WRITE_ERROR;
	free(matrix);
	return WRITE_OK;
}
