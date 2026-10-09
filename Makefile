# --- Compilers ---
CC := cc
AS := cc
CFLAGS := -Wall -Wextra -Werror
ASFLAGS :=

# --- Directories ---
SRC_DIR := src
OBJ_DIR := build
TARGET := bin/hexDumper

# --- Sources ---
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
S_SRCS := $(wildcard $(SRC_DIR)/*.S) $(wildcard $(SRC_DIR)/*.s)

# --- Objects ---
OBJS := $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) 	\
		$(S_SRCS:$(SRC_DIR)/%.S=$(OBJ_DIR)/%.o)		\
		#$(S_SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)	

# --- Default Target ---
all: $(TARGET)

# --- Build Target ---
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	$(AS) $(ASFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) -c -o $@ $<

# --- Clean Target ---
.PHONY: all clean
clean:
	rm -f $(OBJS) $(TARGET)