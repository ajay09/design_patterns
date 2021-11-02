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


$(BUILD_DIR)/1_basic_state_1: $(SRC_DIR)/1_basic_state_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_state_1: $(BUILD_DIR)/1_basic_state_1
	$<

.PHONY : 1_basic_state_1


$(BUILD_DIR)/1_lamp_1: $(SRC_DIR)/1_lamp_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_lamp_1: $(BUILD_DIR)/1_lamp_1
	$<

.PHONY : 1_lamp_1


$(BUILD_DIR)/1_lamp_2: $(SRC_DIR)/1_lamp_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_lamp_2: $(BUILD_DIR)/1_lamp_2
	$<

.PHONY : 1_lamp_2


$(BUILD_DIR)/1_lamp_3: $(SRC_DIR)/1_lamp_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_lamp_3: $(BUILD_DIR)/1_lamp_3
	$<

.PHONY : 1_lamp_3



$(BUILD_DIR)/1_lamp_4: $(SRC_DIR)/1_lamp_4.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_lamp_4: $(BUILD_DIR)/1_lamp_4
	$<

.PHONY : 1_lamp_4


$(BUILD_DIR)/1_lamp_5: $(SRC_DIR)/1_lamp_5.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_lamp_5: $(BUILD_DIR)/1_lamp_5
	$<

.PHONY : 1_lamp_5


$(BUILD_DIR)/1_lamp_6: $(SRC_DIR)/1_lamp_6.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_lamp_6: $(BUILD_DIR)/1_lamp_6
	$<

.PHONY : 1_lamp_6




	











