#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(){

	// открываем файл для чтения
	FILE *file_path = fopen("land.bmp", "r+b");
	if (file_path == NULL) {
		printf(">> BMP not found <<");
		return 1;
	}
	// выделяем память под изображение
	struct image* img = (struct image*)malloc(sizeof(struct image));
	// считываем изображение, проверяя корректность
	int err = from_bmp(file_path, img);
	fclose(file_path);
	if (err) {
		print_error(err);
		return 1;
	}

	// поворот на 90 по часовой стрелке	
	rotate(img, RIGHT);
	FILE *right_img = fopen("right.bmp", "w+b");
	if (to_bmp(right_img, img))
		printf(" >> Rotate error! << \n");
	rotate(img, LEFT);

	 printf("Done! \n");
	 return 0;
}
