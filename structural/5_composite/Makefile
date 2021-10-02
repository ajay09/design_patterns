CC := g++
# c++14 for make_unique
CFLAGS := -g -O0 -Wall -std=c++14
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)




$(BUILD_DIR)/1_basic_composite : $(SRC_DIR)/1_basic_composite.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_basic_composite : $(BUILD_DIR)/1_basic_composite
	$<

.PHONY : 1_basic_composite


$(BUILD_DIR)/2_ui_1 : $(SRC_DIR)/2_ui_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_ui_1 : $(BUILD_DIR)/2_ui_1
	$<

.PHONY : 2_ui_1


$(BUILD_DIR)/2_stream_1 : $(SRC_DIR)/2_stream_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_stream_1 : $(BUILD_DIR)/2_stream_1
	$<

.PHONY : 2_stream_1


$(BUILD_DIR)/2_stream_2 : $(SRC_DIR)/2_stream_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_stream_2 : $(BUILD_DIR)/2_stream_2
	$<

.PHONY : 2_stream_2


$(BUILD_DIR)/2_stream_3 : $(SRC_DIR)/2_stream_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_stream_3 : $(BUILD_DIR)/2_stream_3
	$<

.PHONY : 2_stream_3


$(BUILD_DIR)/2_stream_4 : $(SRC_DIR)/2_stream_4.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_stream_4 : $(BUILD_DIR)/2_stream_4
	$<

.PHONY : 2_stream_4


$(BUILD_DIR)/2_stream_5 : $(SRC_DIR)/2_stream_5.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_stream_5 : $(BUILD_DIR)/2_stream_5
	$<

.PHONY : 2_stream_5


$(BUILD_DIR)/3_static_decorator : $(SRC_DIR)/3_static_decorator.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
3_static_decorator : $(BUILD_DIR)/3_static_decorator
	$<

.PHONY : 3_static_decorator


$(BUILD_DIR)/4_functional_Decorator_1 : $(SRC_DIR)/4_functional_Decorator_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_functional_Decorator_1 : $(BUILD_DIR)/4_functional_Decorator_1
	$<

.PHONY : 4_functional_Decorator_1



$(BUILD_DIR)/4_functional_Decorator_2 : $(SRC_DIR)/4_functional_Decorator_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_functional_Decorator_2 : $(BUILD_DIR)/4_functional_Decorator_2
	$<

.PHONY : 4_functional_Decorator_2



$(BUILD_DIR)/4_functional_Decorator_3 : $(SRC_DIR)/4_functional_Decorator_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
4_functional_Decorator_3 : $(BUILD_DIR)/4_functional_Decorator_3
	$<

.PHONY : 4_functional_Decorator_3
	


$(BUILD_DIR)/5_smart_proxy_2 : $(SRC_DIR)/5_smart_proxy_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
5_smart_proxy_2 : $(BUILD_DIR)/5_smart_proxy_2
	$<

.PHONY : 5_smart_proxy_2






clean :
	rm -rf build

.PHONY : clean
