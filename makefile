main: main.c
		gcc main.c io.c image_rotation.c -o main -std=c18 -pedantic -Wall -Werror