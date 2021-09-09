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


$(BUILD_DIR)/1_basic_factory_method : $(SRC_DIR)/1_basic_factory_method.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_factory_method : $(BUILD_DIR)/1_basic_factory_method
	$<

.PHONY : 1_basic_factory_method



$(BUILD_DIR)/1_basic_factory_method_2 : $(SRC_DIR)/1_basic_factory_method_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_factory_method_2 : $(BUILD_DIR)/1_basic_factory_method_2
	$<
	
.PHONY : 1_basic_factory_method_2

$(BUILD_DIR)/2_app_framework_1 : $(SRC_DIR)/2_app_framework_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_app_framework_1 : $(BUILD_DIR)/2_app_framework_1
	$<

.PHONY : 2_app_framework_1


$(BUILD_DIR)/3_parameterised_factory_method : $(SRC_DIR)/3_parameterised_factory_method.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_parameterised_factory_method : $(BUILD_DIR)/3_parameterised_factory_method
	$<

.PHONY : 3_parameterised_factory_method



$(BUILD_DIR)/2_app_framework_2 : $(SRC_DIR)/2_app_framework_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_app_framework_2 : $(BUILD_DIR)/2_app_framework_2
	$<

.PHONY : 2_app_framework_2


$(BUILD_DIR)/3_factory : $(SRC_DIR)/3_factory.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_factory : $(BUILD_DIR)/3_factory
	$<

.PHONY : 3_factory


$(BUILD_DIR)/4_innerFactory : $(SRC_DIR)/4_innerFactory.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_innerFactory : $(BUILD_DIR)/4_innerFactory
	$<

.PHONY : 4_innerFactory


$(BUILD_DIR)/5_abstractFactory : $(SRC_DIR)/5_abstractFactory.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
5_abstractFactory : $(BUILD_DIR)/5_abstractFactory
	$<

.PHONY : 5_abstractFactory

$(BUILD_DIR)/6_functionalFactory : $(SRC_DIR)/6_functionalFactory.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
6_functionalFactory : $(BUILD_DIR)/6_functionalFactory
	$<

.PHONY : 5_abstractFactory


clean :
	rm -rf build

.PHONY : clean
