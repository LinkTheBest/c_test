
#ifndef BMP_LIB_H
#define BMP_LIB_H

#include <stdint.h>

struct __attribute__((packed)) bmp_header 
{
    uint16_t bfType;
	uint32_t bfileSize;
	uint32_t bfReserved;
	uint32_t bOffBits;
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;

};

 struct pixel {
	uint8_t b, g, r;
};


 struct image {
	uint64_t width, height;
	struct pixel* data;
};

 enum write_status {
	WRITE_OK = 0,
	WRITE_ERROR = 1
};


 enum read_status {
	READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER

};

 enum side{
	LEFT = 0,
	RIGHT = 1,
};

enum read_status read_header(FILE*, struct bmp_header* );
enum read_status read_pixels(FILE*, struct bmp_header* , struct pixel* data);
enum write_status to_bmp(FILE*, const struct image* const);
enum read_status from_bmp(FILE* const, struct image* const);
void rotate(struct image*, enum side);
void print_error(int);

#endif