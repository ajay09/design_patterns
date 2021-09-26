CC := g++
# c++14 for make_unique
CFLAGS := -g -O0 -Wall -Werror -std=c++14
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)




$(BUILD_DIR)/1_basic_facade : $(SRC_DIR)/1_basic_facade.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_facade : $(BUILD_DIR)/1_basic_facade
	$<

.PHONY : 1_basic_facade


$(BUILD_DIR)/4_game_input : $(SRC_DIR)/4_game_input.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_game_input : $(BUILD_DIR)/4_game_input
	$<

.PHONY : 4_game_input


$(BUILD_DIR)/4_game_input_adapter : $(SRC_DIR)/4_game_input_adapter.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_game_input_adapter : $(BUILD_DIR)/4_game_input_adapter
	$<

.PHONY : 4_game_input_adapter


$(BUILD_DIR)/5_class_adapter : $(SRC_DIR)/5_class_adapter.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
5_class_adapter : $(BUILD_DIR)/5_class_adapter
	$<

.PHONY : 5_class_adapter





clean :
	rm -rf build

.PHONY : clean
