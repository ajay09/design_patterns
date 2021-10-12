CC := g++
CFLAGS := -g -O0 -std=c++14 #-Wall -Werror 
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build


last : $(basename $(notdir $(LAST_MODIFIED)))
# 	echo $<

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

.PHONY : strategy_static


$(BUILD_DIR)/1_basic_strategy : $(SRC_DIR)/1_basic_strategy.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
1_basic_strategy : $(BUILD_DIR)/1_basic_strategy
	$<

.PHONY : 1_basic_strategy



$(BUILD_DIR)/2_spreadsheet_app_1 : $(SRC_DIR)/2_spreadsheet_app_1.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
2_spreadsheet_app_1 : $(BUILD_DIR)/2_spreadsheet_app_1
	$<

.PHONY : 2_spreadsheet_app_1


$(BUILD_DIR)/2_spreadsheet_app_2 : $(SRC_DIR)/2_spreadsheet_app_2.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
2_spreadsheet_app_2 : $(BUILD_DIR)/2_spreadsheet_app_2
	$<

.PHONY : 2_spreadsheet_app_2


$(BUILD_DIR)/2_spreadsheet_app_3 : $(SRC_DIR)/2_spreadsheet_app_3.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
2_spreadsheet_app_3 : $(BUILD_DIR)/2_spreadsheet_app_3
	$<

.PHONY : 2_spreadsheet_app_3


$(BUILD_DIR)/3_dynamic_array_1 : $(SRC_DIR)/3_dynamic_array_1.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_1 : $(BUILD_DIR)/3_dynamic_array_1
	$<

.PHONY : 3_dynamic_array_1


$(BUILD_DIR)/3_dynamic_array_2 : $(SRC_DIR)/3_dynamic_array_2.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_2 : $(BUILD_DIR)/3_dynamic_array_2
	$<

.PHONY : 3_dynamic_array_2


$(BUILD_DIR)/3_dynamic_array_3 : $(SRC_DIR)/3_dynamic_array_3.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_3 : $(BUILD_DIR)/3_dynamic_array_3
	$<

.PHONY : 3_dynamic_array_3



$(BUILD_DIR)/3_dynamic_array_4 : $(SRC_DIR)/3_dynamic_array_4.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_4 : $(BUILD_DIR)/3_dynamic_array_4
	$<

.PHONY : 3_dynamic_array_4




$(BUILD_DIR)/3_dynamic_array_5 : $(SRC_DIR)/3_dynamic_array_5.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_5 : $(BUILD_DIR)/3_dynamic_array_5
	$<

.PHONY : 3_dynamic_array_5






