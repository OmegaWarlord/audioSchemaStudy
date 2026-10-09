# --- Compilers ---
CC := cc
AS := cc
CFLAGS := -Wall -Wextra -Werror
ASFLAGS :=

# --- Directories ---
SRC_DIR := src
OBJ_DIR := obj
TARGET := bin/hexDumper

# --- Sources ---
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
S_SRCS := $(wildcard $(SRC_DIR)/*.S) $(wildcard $(SRC_DIR)/*.s)

# --- Objects ---
OBJS := $(C_SRCS:.c=.o) $(S_SRCS:.S=.o) #$(S_SRCS:.s=.o)

# --- Default Target ---
all: $(TARGET)

# --- Build Target ---
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: $(SRC_DIR)/%.S
	$(AS) $(ASFLAGS) -c -o $@ $<

%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) -c -o $@ $<

# --- Clean Target ---
.PHONY: all clean
clean:
	rm -f $(OBJS) $(TARGET)