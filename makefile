CC = gcc
EXECUTABLE_FILE_NAME = program
SRC = src/
SRC_DOT_C_FILES = $(wildcard $(SRC)*.c) 
BUILD_DIR = build/

EXECUTABLE = $(BUILD_DIR)$(EXECUTABLE_FILE_NAME)
COMPILED_FILES = $(addprefix $(BUILD_DIR), $(notdir $(SRC_DOT_C_FILES:.c=.o)))

FLAGS = -std=c18 -pedantic -Wall -Werror


all: $(EXECUTABLE)

$(EXECUTABLE): $(COMPILED_FILES)
	$(CC) -o $(EXECUTABLE) $^

$(COMPILED_FILES): $(BUILD_DIR)%.o: $(SRC)%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(FLAGS) $< -o $@ 

clean: 
	rm -rf *.o $(BUILD_DIR)