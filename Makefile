CC = gcc

INCLUDES = -Iinclude -Iinclude/binary_converter -Iinclude/database -Iinclude/database/user -Iinclude/database/data -Iinclude/ui

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS := $(wildcard $(SRC_DIR)/*.c) \
        $(wildcard $(SRC_DIR)/*/*.c) \
        $(wildcard $(SRC_DIR)/*/*/*.c)

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBS = -lmysqlclient -lncurses

EXEC = main

all: $(BIN_DIR)/$(EXEC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/database/user $(OBJ_DIR)/database/data $(OBJ_DIR)/binary_converter $(OBJ_DIR)/ui/admin

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/**/*.o $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXEC)
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

