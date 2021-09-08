CC := g++
CFLAGS := -g -O0 -Wall -Werror -std=c++14
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build


last : $(basename $(notdir $(LAST_MODIFIED)))
	echo $<

.PHONY : last

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/strategy : $(SRC_DIR)/strategy.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
strategy : $(BUILD_DIR)/strategy
	$<

.PHONY : strategy


$(BUILD_DIR)/strategy_static : $(SRC_DIR)/strategy_static.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
strategy_static : $(BUILD_DIR)/strategy_static
	$<

.PHONY : strategy