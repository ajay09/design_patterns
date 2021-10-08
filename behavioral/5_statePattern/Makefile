CC := g++
CFLAGS := -g -O0 -Wall -Werror -std=c++11
BOOST_INCLUDE := - L /Users/ajay/homebrew/Cellar/boost/1.76.0
BOOST_LIB_DIR := /Users/ajay/homebrew/Cellar/boost/1.76.0/lib
BOOST_LIB := -L $(BOOST_LIB_DIR) -lboost-system
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build

LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/state: $(SRC_DIR)/state.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
# 	$(CC) $(CFLAGS) -I $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
state: $(BUILD_DIR)/state
	$<

.PHONY : state