SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./build/obj
BIN_DIR = ./build/bin
DOC_DIR = ./build/doc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRC_FILES))
CFLAGS = -I$(INC_DIR) -Wall

all: $(BIN_DIR)/app.out

$(BIN_DIR)/app.out: $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	gcc $(OBJ_FILES) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) -c $< -o $@

doc:
	@mkdir -p $(DOC_DIR)
	doxygen Doxyfile

format:
	clang-format -i $(SRC_DIR)/*.c $(INC_DIR)/*.h

clean:
	rm -rf build
