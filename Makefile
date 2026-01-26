CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
CPPFLAGS = -Iheaders
OBJ_DIR = out
TARGET  = $(OBJ_DIR)/neoarch
SRC     = main.c utils/system.c
OBJ      = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean


.PHONY: all clean