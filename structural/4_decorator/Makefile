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




$(BUILD_DIR)/1_basic_decorator_1 : $(SRC_DIR)/1_basic_decorator_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_decorator_1 : $(BUILD_DIR)/1_basic_decorator_1
	$<

.PHONY : 1_basic_decorator_1


$(BUILD_DIR)/2_virtual_proxy_1 : $(SRC_DIR)/2_virtual_proxy_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_virtual_proxy_1 : $(BUILD_DIR)/2_virtual_proxy_1
	$<

.PHONY : 2_virtual_proxy_1


$(BUILD_DIR)/2_virtual_proxy_2 : $(SRC_DIR)/2_virtual_proxy_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_virtual_proxy_2 : $(BUILD_DIR)/2_virtual_proxy_2
	$<

.PHONY : 2_virtual_proxy_2


$(BUILD_DIR)/3_protection_proxy_1 : $(SRC_DIR)/3_protection_proxy_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_protection_proxy_1 : $(BUILD_DIR)/3_protection_proxy_1
	$<

.PHONY : 3_protection_proxy_1


$(BUILD_DIR)/3_protection_proxy_2 : $(SRC_DIR)/3_protection_proxy_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_protection_proxy_2 : $(BUILD_DIR)/3_protection_proxy_2
	$<

.PHONY : 3_protection_proxy_2


$(BUILD_DIR)/4_remote_proxy_1 : $(SRC_DIR)/4_remote_proxy_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_remote_proxy_1 : $(BUILD_DIR)/4_remote_proxy_1
	$<

.PHONY : 4_remote_proxy_1



$(BUILD_DIR)/4_remote_proxy_2 : $(SRC_DIR)/4_remote_proxy_2.cpp $(BUILD_DIR)
# 	$(CC) $(CFLAGS) -o $@ $<
4_remote_proxy_2 : $(BUILD_DIR)/4_remote_proxy_2
# 	$<

.PHONY : 4_remote_proxy_2



$(BUILD_DIR)/5_smart_proxy_1 : $(SRC_DIR)/5_smart_proxy_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
5_smart_proxy_1 : $(BUILD_DIR)/5_smart_proxy_1
	$<

.PHONY : 5_smart_proxy_1
	


$(BUILD_DIR)/5_smart_proxy_2 : $(SRC_DIR)/5_smart_proxy_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
5_smart_proxy_2 : $(BUILD_DIR)/5_smart_proxy_2
	$<

.PHONY : 5_smart_proxy_2






clean :
	rm -rf build

.PHONY : clean
