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



$(BUILD_DIR)/1_basic_CommandPattern_1 : $(SRC_DIR)/1_basic_CommandPattern_1.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
1_basic_CommandPattern_1 : $(BUILD_DIR)/1_basic_CommandPattern_1
	$<

.PHONY : 1_basic_CommandPattern_1



$(BUILD_DIR)/1_basic_CommandPattern_2 : $(SRC_DIR)/1_basic_CommandPattern_2.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
1_basic_CommandPattern_2 : $(BUILD_DIR)/1_basic_CommandPattern_2
	$<

.PHONY : 1_basic_CommandPattern_2


$(BUILD_DIR)/2_find_dialog_1 : $(SRC_DIR)/2_find_dialog_1.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
2_find_dialog_1 : $(BUILD_DIR)/2_find_dialog_1
	$<

.PHONY : 2_find_dialog_1


$(BUILD_DIR)/3_text_pad_1 : $(SRC_DIR)/3_text_pad_1.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_text_pad_1 : $(BUILD_DIR)/3_text_pad_1
	$<

.PHONY : 3_text_pad_1


$(BUILD_DIR)/3_text_pad_2 : $(SRC_DIR)/3_text_pad_2.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_text_pad_2 : $(BUILD_DIR)/3_text_pad_2
	$<

.PHONY : 3_text_pad_2


$(BUILD_DIR)/3_text_pad_3 : $(SRC_DIR)/3_text_pad_3.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_text_pad_3 : $(BUILD_DIR)/3_text_pad_3
	$<

.PHONY : 3_text_pad_3



$(BUILD_DIR)/3_text_pad_4 : $(SRC_DIR)/3_text_pad_4.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_text_pad_4 : $(BUILD_DIR)/3_text_pad_4
	$<

.PHONY : 3_text_pad_4


$(BUILD_DIR)/3_text_pad_5 : $(SRC_DIR)/3_text_pad_5.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_text_pad_5 : $(BUILD_DIR)/3_text_pad_5
	$<

.PHONY : 3_text_pad_5


$(BUILD_DIR)/3_dynamic_array_6 : $(SRC_DIR)/3_dynamic_array_6.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_6 : $(BUILD_DIR)/3_dynamic_array_6
	$<

.PHONY : 3_dynamic_array_6


$(BUILD_DIR)/3_dynamic_array_7 : $(SRC_DIR)/3_dynamic_array_7.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_7 : $(BUILD_DIR)/3_dynamic_array_7
	$<

.PHONY : 3_dynamic_array_7


$(BUILD_DIR)/3_dynamic_array_8 : $(SRC_DIR)/3_dynamic_array_8.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
3_dynamic_array_8 : $(BUILD_DIR)/3_dynamic_array_8
	$<

.PHONY : 3_dynamic_array_8


$(BUILD_DIR)/4_static_strategy : $(SRC_DIR)/4_static_strategy.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
4_static_strategy : $(BUILD_DIR)/4_static_strategy
	$<

.PHONY : 4_static_strategy


$(BUILD_DIR)/5_function_strategy_1 : $(SRC_DIR)/5_function_strategy_1.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
5_function_strategy_1 : $(BUILD_DIR)/5_function_strategy_1
	$<

.PHONY : 5_function_strategy_1


$(BUILD_DIR)/5_function_strategy_2 : $(SRC_DIR)/5_function_strategy_2.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
5_function_strategy_2 : $(BUILD_DIR)/5_function_strategy_2
	$<

.PHONY : 5_function_strategy_2




clean :
	rm -rf build

