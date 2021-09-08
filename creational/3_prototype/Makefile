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

$(BUILD_DIR)/1_recordKeeping : $(SRC_DIR)/1_recordKeeping.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_recordKeeping : $(BUILD_DIR)/1_recordKeeping
	$<

.PHONY : 1_recordKeeping


$(BUILD_DIR)/2_prototype : $(SRC_DIR)/2_prototype.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_prototype : $(BUILD_DIR)/2_prototype
	$<

.PHONY : 2_prototype


$(BUILD_DIR)/3_prototypeFactory : $(SRC_DIR)/3_prototypeFactory.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_prototypeFactory : $(BUILD_DIR)/3_prototypeFactory
	$<

.PHONY : 3_prototypeFactory





clean :
	rm -rf build

.PHONY : clean
