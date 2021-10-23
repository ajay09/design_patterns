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



$(BUILD_DIR)/1_basic_template_method : $(SRC_DIR)/1_basic_template_method.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
1_basic_template_method : $(BUILD_DIR)/1_basic_template_method
	$<

.PHONY : 1_basic_template_method



$(BUILD_DIR)/2_document_framework_1 : $(SRC_DIR)/2_document_framework_1.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
2_document_framework_1 : $(BUILD_DIR)/2_document_framework_1
	$<

.PHONY : 2_document_framework_1


$(BUILD_DIR)/2_document_framework_2 : $(SRC_DIR)/2_document_framework_2.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
2_document_framework_2 : $(BUILD_DIR)/2_document_framework_2
	$<

.PHONY : 2_document_framework_2


$(BUILD_DIR)/2_document_framework_3 : $(SRC_DIR)/2_document_framework_3.cpp $(BUILD_DIR) 
	$(CC) $(CFLAGS) -o $@ $<
2_document_framework_3 : $(BUILD_DIR)/2_document_framework_3
	$<

.PHONY : 2_document_framework_3



clean :
	rm -rf build

