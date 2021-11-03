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


# 	$(CC) $(CFLAGS) -I $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
$(BUILD_DIR)/1_basic_iterator: $(SRC_DIR)/1_basic_iterator.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_iterator: $(BUILD_DIR)/1_basic_iterator
	$<

.PHONY : 1_basic_iterator


$(BUILD_DIR)/2_organization_1: $(SRC_DIR)/2_organization_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_organization_1: $(BUILD_DIR)/2_organization_1
	$<

.PHONY : 2_organization_1


$(BUILD_DIR)/2_organization_2: $(SRC_DIR)/2_organization_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_organization_2: $(BUILD_DIR)/2_organization_2
	$<

.PHONY : 2_organization_2


$(BUILD_DIR)/3_container_1: $(SRC_DIR)/3_container_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_container_1: $(BUILD_DIR)/3_container_1
	$<

.PHONY : 3_container_1


$(BUILD_DIR)/3_container_2: $(SRC_DIR)/3_container_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_container_2: $(BUILD_DIR)/3_container_2
	$<

.PHONY : 3_container_2



$(BUILD_DIR)/3_container_3: $(SRC_DIR)/3_container_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_container_3: $(BUILD_DIR)/3_container_3
	$<

.PHONY : 3_container_3


$(BUILD_DIR)/3_container_4: $(SRC_DIR)/3_container_4.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_container_4: $(BUILD_DIR)/3_container_4
	$<

.PHONY : 3_container_4


$(BUILD_DIR)/2_lamp_6: $(SRC_DIR)/2_lamp_6.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_lamp_6: $(BUILD_DIR)/2_lamp_6
	$<

.PHONY : 2_lamp_6



$(BUILD_DIR)/3_transition_table_1: $(SRC_DIR)/3_transition_table_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_transition_table_1: $(BUILD_DIR)/3_transition_table_1
	$<

.PHONY : 3_transition_table_1





$(BUILD_DIR)/4_methods_1: $(SRC_DIR)/4_methods_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_methods_1: $(BUILD_DIR)/4_methods_1
	$<

.PHONY : 4_methods_1


$(BUILD_DIR)/4_methods_2: $(SRC_DIR)/4_methods_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_methods_2: $(BUILD_DIR)/4_methods_2
	$<

.PHONY : 4_methods_2



$(BUILD_DIR)/4_methods_3: $(SRC_DIR)/4_methods_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_methods_3: $(BUILD_DIR)/4_methods_3
	$<

.PHONY : 4_methods_3



	











