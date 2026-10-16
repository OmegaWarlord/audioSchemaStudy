# --- Compilers ---
CC := cc
AS := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
ASFLAGS :=

# --- Directories ---
SRC_DIR := src
OBJ_DIR := build
OUT_DIR := output
TARGET_DIR := bin
TARGET := $(TARGET_DIR)/hexDumper

# --- Sources ---
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
S_SRCS := $(wildcard $(SRC_DIR)/*.S) $(wildcard $(SRC_DIR)/*.s)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
OUTPUTS := $(wildcard $(OUT_DIR)/*.*)

# --- Objects ---
OBJS := $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) 	\
		$(S_SRCS:$(SRC_DIR)/%.S=$(OBJ_DIR)/%.o)		\
		#$(S_SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)	

# --- Default Target ---
all: clean $(TARGET)


# --- Order-Only ---
target_dir:
	@mkdir -p $(TARGET_DIR)

obj_dir:
	@mkdir -p $(OBJ_DIR)

# --- Build Target ---
$(TARGET): $(OBJS) | target_dir
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | obj_dir
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S $(HEADERS) | obj_dir
	$(AS) $(ASFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s $(HEADERS) | obj_dir
	$(AS) $(ASFLAGS) -c -o $@ $<

# --- Clean Target ---
.PHONY: all clean
clean:
	@mkdir -p $(OUT_DIR)
	rm -f $(OBJS) $(TARGET) $(OUTPUTS)