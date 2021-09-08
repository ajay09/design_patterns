CC := g++
CFLAGS := -g -O0 -Wall -Werror -std=c++11
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/1_SRP : $(SRC_DIR)/1_SRP.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
1_SRP : $(BUILD_DIR)/1_SRP
	$<

.PHONY : 1_SRP


$(BUILD_DIR)/2_OCP : $(SRC_DIR)/2_OCP.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<
2_OCP : $(BUILD_DIR)/2_OCP
	$<

.PHONY : 2_OCP


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
