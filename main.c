#include <stdio.h>
#include <stdlib.h>
#include "error_printing.h"
#include "bmp_main.h"
#include "bmp_io.h"
#include "image_rotation.h"

#define DEFAULT_OUTPUT_PATH "output.bmp"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char *argv[]){

	if (argc <2) {
        printf(ANSI_COLOR_RED "Invalid arguments! \n"  ANSI_COLOR_BLUE "Example:" 
		ANSI_COLOR_GREEN " input_directory/input_file.bmp " ANSI_COLOR_MAGENTA "outut_directory/output_file.bmp\n" 
		ANSI_COLOR_RESET);
        return 1;
    }
    const char *input_path = argv[1];
    const char *output_path;
    if (argc < 3) {
        output_path = DEFAULT_OUTPUT_PATH;
    } else {
        output_path = argv[2];
    }

	
	FILE *file_path = fopen(input_path, "r+b");
	if (file_path == NULL) {
		printf(">> BMP not found <<");
		return 1;
	}
	
	struct image* img = (struct image*)malloc(sizeof(struct image));

	int err = from_bmp(file_path, img);
	fclose(file_path);
	if (err) {
		error_print(err);
		return 1;
	}

	rotate(img, RIGHT);

	FILE *right_img = fopen(output_path, "w+b");
	if (to_bmp(right_img, img))
		printf(" >> Rotation error! << \n");
	rotate(img, LEFT);
	printf("Done! \n");
	free(img);
	fclose(right_img);
	return 0;
}
