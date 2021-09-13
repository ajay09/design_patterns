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


$(BUILD_DIR)/1_basic_abstract_factory : $(SRC_DIR)/1_basic_abstract_factory.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_abstract_factory : $(BUILD_DIR)/1_basic_abstract_factory
	$<

.PHONY : 1_basic_abstract_factory



$(BUILD_DIR)/1_basic_abstract_factory_2 : $(SRC_DIR)/1_basic_abstract_factory_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_abstract_factory_2 : $(BUILD_DIR)/1_basic_abstract_factory_2
	$<
	
.PHONY : 1_basic_abstract_factory_2


$(BUILD_DIR)/2_database_framework : $(SRC_DIR)/2_database_framework.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_database_framework : $(BUILD_DIR)/2_database_framework
	$<

.PHONY : 2_database_framework


$(BUILD_DIR)/2_MySql_database_framework_2 : $(SRC_DIR)/2_MySql_database_framework_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_MySql_database_framework_2 : $(BUILD_DIR)/2_MySql_database_framework_2
	$<

.PHONY : 2_MySql_database_framework_2



$(BUILD_DIR)/2_MySql_database_framework_3 : $(SRC_DIR)/2_MySql_database_framework_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_MySql_database_framework_3 : $(BUILD_DIR)/2_MySql_database_framework_3
	$<

.PHONY : 2_MySql_database_framework_3


$(BUILD_DIR)/2_MySql_database_framework_4 : $(SRC_DIR)/2_MySql_database_framework_4.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_MySql_database_framework_4 : $(BUILD_DIR)/2_MySql_database_framework_4
	$<

.PHONY : 2_MySql_database_framework_4


$(BUILD_DIR)/2_MySql_database_framework_5 : $(SRC_DIR)/2_MySql_database_framework_5.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_MySql_database_framework_5 : $(BUILD_DIR)/2_MySql_database_framework_5
	$<

.PHONY : 2_MySql_database_framework_5


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
