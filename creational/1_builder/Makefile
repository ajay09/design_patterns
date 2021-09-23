CC := g++
CFLAGS := -g -O0  -std=c++11
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/1_basic_builder : $(SRC_DIR)/1_basic_builder.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_builder : $(BUILD_DIR)/1_basic_builder
	$<

.PHONY : 1_basic_builder


$(BUILD_DIR)/2_file_class : $(SRC_DIR)/2_file_class.cpp $(BUILD_DIR) 	
	$(CC) $(CFLAGS) -o $@ $< 
2_file_class : $(BUILD_DIR)/2_file_class 	

$<  .PHONY : 2_file_class


$(BUILD_DIR)/2_file_class_2 : $(SRC_DIR)/2_file_class_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_file_class_2 : $(BUILD_DIR)/2_file_class_2
	$<

.PHONY : 2_file_class_2


$(BUILD_DIR)/2_file_class_3 : $(SRC_DIR)/2_file_class_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_file_class_3 : $(BUILD_DIR)/2_file_class_3
	$<

.PHONY : 2_file_class_3


$(BUILD_DIR)/2_file_class_4 : $(SRC_DIR)/2_file_class_4.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_file_class_4 : $(BUILD_DIR)/2_file_class_4
	$<

.PHONY : 2_file_class_4


$(BUILD_DIR)/3_LSP : $(SRC_DIR)/3_LSP.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_LSP : $(BUILD_DIR)/3_LSP
	$<

.PHONY : 3_LSP


$(BUILD_DIR)/4_ISP : $(SRC_DIR)/4_ISP.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_ISP : $(BUILD_DIR)/4_ISP
	$<

.PHONY : 4_ISP


clean :
	rm -rf build

.PHONY : clean
