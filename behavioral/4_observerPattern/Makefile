CC := g++
BOOST_LIB_DIR := /Users/ajay/homebrew/Cellar/boost/1.76.0/lib
BOOST_LIB := -L $(BOOST_LIB_DIR) -lboost_system # for linking boost library
CFLAGS := -g -O0 -Wall -std=c++11
SRC_DIR := .
BUILD_DIR := build
INCLUDE := -I /Users/ajay/homebrew/Cellar/boost/1.76.0/include
RECENTLY_MODIFIED_FILE := $(shell ls -rt *.cpp | tail -n 1)

# compile and run the last modified file
last : $(notdir $(basename $(RECENTLY_MODIFIED_FILE)))
	@ echo $(RECENTLY_MODIFIED_FILE)

.PHONY : last


$(BUILD_DIR):
	@ mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/observer: $(SRC_DIR)/observer.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
observer: $(BUILD_DIR)/observer
	$<

.PHONY : observer


$(BUILD_DIR)/observer2: $(SRC_DIR)/observer2.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
observer2: $(BUILD_DIR)/observer2
	$<

.PHONY : observer2


$(BUILD_DIR)/observer3: $(SRC_DIR)/observer3.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
observer3: $(BUILD_DIR)/observer3
	$<

.PHONY : observer3


$(BUILD_DIR)/1_basic_observer: $(SRC_DIR)/1_basic_observer.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
1_basic_observer: $(BUILD_DIR)/1_basic_observer
	$<

.PHONY : 1_basic_observer







clean :
	rm -rf build

.PHONY : clean
