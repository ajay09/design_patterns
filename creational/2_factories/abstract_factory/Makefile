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


$(BUILD_DIR)/2_missile_game_2 : $(SRC_DIR)/2_missile_game_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_missile_game_2 : $(BUILD_DIR)/2_missile_game_2
	$<

.PHONY : 2_missile_game_2


$(BUILD_DIR)/3_multiple_actors : $(SRC_DIR)/3_multiple_actors.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_multiple_actors : $(BUILD_DIR)/3_multiple_actors
	$<

.PHONY : 3_multiple_actors



$(BUILD_DIR)/3_multiple_actors_2 : $(SRC_DIR)/3_multiple_actors_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_multiple_actors_2 : $(BUILD_DIR)/3_multiple_actors_2
	$<

.PHONY : 3_multiple_actors_2


$(BUILD_DIR)/4_generic_pool_1 : $(SRC_DIR)/4_generic_pool_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_generic_pool_1 : $(BUILD_DIR)/4_generic_pool_1
	$<

.PHONY : 4_generic_pool_1


$(BUILD_DIR)/4_generic_pool_2 : $(SRC_DIR)/4_generic_pool_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_generic_pool_2 : $(BUILD_DIR)/4_generic_pool_2
	$<

.PHONY : 4_generic_pool_2


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
