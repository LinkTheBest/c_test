#include <stdio.h>
#include <stdlib.h>
#include "bmp_main.h"
#include "bmp_io.h"
#include "image_rotation.h"
#include "image_struct.h"

#define RED(...){ printf(ANSI_COLOR_RED __VA_ARGS__);}
#define BLUE(...){ printf(ANSI_COLOR_BLUE __VA_ARGS__);}
#define GREEN(...){ printf(ANSI_COLOR_GREEN __VA_ARGS__);}
#define MAGENTA(...){ printf(ANSI_COLOR_MAGENTA __VA_ARGS__);}
#define RESET(...){ printf(ANSI_COLOR_RESET __VA_ARGS__);}

int main(int argc, char *argv[]){

	if (argc <2) {
		RED("Invalid arguments! \n");
		BLUE("Example:");
		GREEN(" input_directory/input_file.bmp ");
		MAGENTA("outut_directory/output_file.bmp\n")
		RESET("");
        return 1;
    }
    const char *input_path = argv[1];
    const char *output_path;
    if (argc < 3) {
		RED("No output source, file will be saved in root directory!\n");
		RESET("");
        output_path = DEFAULT_OUTPUT_PATH;
    } else {
        output_path = argv[2];
    }

	
	FILE *file_path = fopen(input_path, "r+b");
	if (file_path == NULL) {
		printf(">> BMP not found <<");
		return 1;
	}
	
	struct image img;

	enum read_status err = from_bmp(file_path, &img);
	fclose(file_path);
	if (err) {
		return err;
	}

	img = rotate(&img, RIGHT);

	FILE *right_img = fopen(output_path, "w+b");
	if (to_bmp(right_img, &img))
		printf(" >> Rotation error! << \n");
	rotate(&img, LEFT);
	MAGENTA("Done! \n" );
	RESET("");
	fclose(right_img);
	return 0;
}
