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
OUTPUTS := $(wildcard $(OUT_DIR)/*)

# --- Objects ---
OBJS := $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) 	\
		$(S_SRCS:$(SRC_DIR)/%.S=$(OBJ_DIR)/%.o)		\
		#$(S_SRCS:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)	

# --- Functions ---
all: $(TARGET)

check: #change to order-only prereq at some point
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(TARGET_DIR)

clean:
	rm -f $(OUTPUTS) $(OBJS) $(TARGET)

# --- Build Target ---
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S $(HEADERS)
	$(AS) $(ASFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s $(HEADERS)
	$(AS) $(ASFLAGS) -c -o $@ $<

# --- Default ---
.PHONY: all check clean