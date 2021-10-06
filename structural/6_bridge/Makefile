CC := g++

BOOST_LIB_DIR := /Users/ajay/homebrew/lib
BOOST_LIB := -L $(BOOST_LIB_DIR) -lsimple2d -lSDL2 -Wl,-framework,OpenGL -lSDL2_image -lSDL2_mixer -lSDL2_ttf

CFLAGS := -g -O0 -std=c++14  -D_THREAD_SAFE
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build

BOOST_INCLUDE := -I/Users/ajay/homebrew/include -I/Users/ajay/homebrew/include/SDL2

LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)



$(BUILD_DIR)/lib_test: $(SRC_DIR)/lib_test.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
lib_test: $(BUILD_DIR)/lib_test
	$<

.PHONY : lib_test


$(BUILD_DIR)/1_basic_bridge: $(SRC_DIR)/1_basic_bridge.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
1_basic_bridge: $(BUILD_DIR)/1_basic_bridge
	$<

.PHONY : 1_basic_bridge


$(BUILD_DIR)/2_shapes_1: $(SRC_DIR)/2_shapes_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
2_shapes_1: $(BUILD_DIR)/2_shapes_1
	$<

.PHONY : 2_shapes_1


$(BUILD_DIR)/2_shapes_2: $(SRC_DIR)/2_shapes_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
2_shapes_2: $(BUILD_DIR)/2_shapes_2
	$<

.PHONY : 2_shapes_2


$(BUILD_DIR)/2_shapes_3: $(SRC_DIR)/2_shapes_3.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
2_shapes_3: $(BUILD_DIR)/2_shapes_3
	$<

.PHONY : 2_shapes_3




$(BUILD_DIR)/2_shapes_4: $(SRC_DIR)/2_shapes_4.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
2_shapes_4: $(BUILD_DIR)/2_shapes_4
	$<

.PHONY : 2_shapes_4



$(BUILD_DIR)/3_handle_body_1: $(SRC_DIR)/3_handle_body_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -D TRACE $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
3_handle_body_1: $(BUILD_DIR)/3_handle_body_1
	$<

.PHONY : 3_handle_body_1


$(BUILD_DIR)/3_handle_body_2: $(SRC_DIR)/3_handle_body_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -D TRACE $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
3_handle_body_2: $(BUILD_DIR)/3_handle_body_2
	$<

.PHONY : 3_handle_body_2


$(BUILD_DIR)/4_PIMPL_1: $(SRC_DIR)/4_PIMPL_1.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -D TRACE $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
4_PIMPL_1: $(BUILD_DIR)/4_PIMPL_1
	$<

.PHONY : 4_PIMPL_1


$(BUILD_DIR)/4_PIMPL_2: $(SRC_DIR)/4_PIMPL_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -D TRACE $(BOOST_INCLUDE) $(BOOST_LIB) -o $@ $<
4_PIMPL_2: $(BUILD_DIR)/4_PIMPL_2
	$<

.PHONY : 4_PIMPL_2









clean :
	rm -rf build

.PHONY : clean


