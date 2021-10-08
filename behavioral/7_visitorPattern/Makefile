CC := g++
CFLAGS := -g -O0 -Wall -Wextra -std=c++14
SRC_DIR := .
BUILD_DIR := build

LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))
	@ echo $<

.PHONY : last

visitor1 : $(BUILD_DIR)/visitor1
	$<
	
.PHONY : visitor1

$(BUILD_DIR)/visitor1 : $(SRC_DIR)/visitor1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR) : 
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY : clean


visitor2 : $(BUILD_DIR)/visitor2
	$<
	
.PHONY : visitor2

$(BUILD_DIR)/visitor2 : $(SRC_DIR)/visitor2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<




visitor3 : $(BUILD_DIR)/visitor3
	$<
	
.PHONY : visitor2

$(BUILD_DIR)/visitor3 : $(SRC_DIR)/visitor3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<