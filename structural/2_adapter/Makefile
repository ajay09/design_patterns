CC := g++
# c++14 for make_unique
BOOST_LIB_DIR := /Users/ajay/homebrew/Cellar/boost/1.76.0/lib
GTEST_LIB_DIR := /Users/ajay/homebrew/lib/
BOOST_LIB := -L $(BOOST_LIB_DIR) -lboost_system # for linking boost library
GTEST_LIB := -L $(GTEST_LIB_DIR) -lgtest -lgtest_main
CFLAGS := -g -O0 -Wall -Werror -std=c++14
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build
INCLUDE := -I /Users/ajay/homebrew/Cellar/boost/1.76.0/include -I /Users/ajay/homebrew/include/
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/1_adapter : $(SRC_DIR)/1_adapter.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
1_adapter : $(BUILD_DIR)/1_adapter
	$<

.PHONY : 1_adapter


$(BUILD_DIR)/2_adapter : $(SRC_DIR)/2_adapter.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
2_adapter : $(BUILD_DIR)/2_adapter
	$<

.PHONY : 2_adapter


$(BUILD_DIR)/3_adapter : $(SRC_DIR)/3_adapter.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_adapter : $(BUILD_DIR)/3_adapter
	$<

.PHONY : 3_adapter


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
