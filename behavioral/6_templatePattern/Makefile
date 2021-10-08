CC := g++
CFLAGS := -g -O0 -Wall -Werror -std=c++14
SRC_DIR := .
BUILD_DIR := build


template_method : $(BUILD_DIR)/template_method
	$<


$(BUILD_DIR)/template_method : $(SRC_DIR)/template_method.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR) :
	mkdir -p build