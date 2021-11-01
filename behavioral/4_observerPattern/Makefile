CC := g++
BOOST_LIB_DIR := /Users/ajay/homebrew/Cellar/boost/1.76.0/lib
BOOST_LIB := -L $(BOOST_LIB_DIR) -lboost_system # for linking boost library
CFLAGS := -g -O0 -Wall -std=c++14
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


$(BUILD_DIR)/2_alert_system_1: $(SRC_DIR)/2_alert_system_1.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
2_alert_system_1: $(BUILD_DIR)/2_alert_system_1
	$<

.PHONY : 2_alert_system_1


$(BUILD_DIR)/2_alert_system_2: $(SRC_DIR)/2_alert_system_2.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
2_alert_system_2: $(BUILD_DIR)/2_alert_system_2
	$<

.PHONY : 2_alert_system_2



$(BUILD_DIR)/3_slide_deck_1: $(SRC_DIR)/3_slide_deck_1.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
3_slide_deck_1: $(BUILD_DIR)/3_slide_deck_1
	$<

.PHONY : 3_slide_deck_1


$(BUILD_DIR)/3_slide_deck_2: $(SRC_DIR)/3_slide_deck_2.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
3_slide_deck_2: $(BUILD_DIR)/3_slide_deck_2
	$<

.PHONY : 3_slide_deck_2


$(BUILD_DIR)/3_slide_deck_3: $(SRC_DIR)/3_slide_deck_3.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
3_slide_deck_3: $(BUILD_DIR)/3_slide_deck_3
	$<

.PHONY : 3_slide_deck_3



$(BUILD_DIR)/3_slide_deck_4: $(SRC_DIR)/3_slide_deck_4.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
3_slide_deck_4: $(BUILD_DIR)/3_slide_deck_4
	$<

.PHONY : 3_slide_deck_4



$(BUILD_DIR)/4_sensor_1: $(SRC_DIR)/4_sensor_1.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
4_sensor_1: $(BUILD_DIR)/4_sensor_1
	$<

.PHONY : 4_sensor_1




$(BUILD_DIR)/4_sensor_2: $(SRC_DIR)/4_sensor_2.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
4_sensor_2: $(BUILD_DIR)/4_sensor_2
	$<

.PHONY : 4_sensor_2


$(BUILD_DIR)/5_change_manager: $(SRC_DIR)/5_change_manager.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) -o $@ $<
5_change_manager: $(BUILD_DIR)/5_change_manager
	$<

.PHONY : 5_change_manager



clean :
	rm -rf build

.PHONY : clean
