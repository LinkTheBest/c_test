
#ifndef BMP_IO
#define BMP_IO
#include <stdint.h>
#include "bmp_main.h"


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

#endif
