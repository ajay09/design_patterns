CC := g++
# c++14 for make_unique
BOOST_LIB_DIR := /Users/ajay/homebrew/Cellar/boost/1.76.0/lib
GTEST_LIB_DIR := /Users/ajay/homebrew/lib/
BOOST_LIB := -L $(BOOST_LIB_DIR) -lboost_system # for linking boost library
GTEST_LIB := -L $(GTEST_LIB_DIR) -lgtest -lgtest_main
CFLAGS := -g -O0 -Wall -Werror -std=c++14
SRC_DIR := .
BUILD_DIR := $(SRC_DIR)/build
INCLUDE := -I /Users/ajay/homebrew/Cellar/boost/1.76.0/include -I /Users/ajay/homebrew/include/
LAST_MODIFIED := $(shell ls -rt *.cpp | tail -n 1)

last : $(basename $(notdir $(LAST_MODIFIED)))

.PHONY : last

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/0_issue : $(SRC_DIR)/0_issue.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
0_issue : $(BUILD_DIR)/0_issue
	$<

$(BUILD_DIR)/0_issue_sol : $(SRC_DIR)/0_issue_sol.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
0_issue_sol : $(BUILD_DIR)/0_issue_sol
	$<

$(BUILD_DIR)/2_singletonTests : $(SRC_DIR)/2_singletonTests.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
2_singletonTests : $(BUILD_DIR)/2_singletonTests
	$<

.PHONY : 2_singletonTests

$(BUILD_DIR)/3_singletonTests : $(SRC_DIR)/3_singletonTests.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
3_singletonTests : $(BUILD_DIR)/3_singletonTests
	$<

.PHONY : 3_singletonTests

$(BUILD_DIR)/4_singletonTests : $(SRC_DIR)/4_singletonTests.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
4_singletonTests : $(BUILD_DIR)/4_singletonTests
	$<

.PHONY : 4_singletonTests

$(BUILD_DIR)/5_lazy_instantiation : $(SRC_DIR)/5_lazy_instantiation.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
5_lazy_instantiation : $(BUILD_DIR)/5_lazy_instantiation
	$<

$(BUILD_DIR)/6_singleton_destruction : $(SRC_DIR)/6_singleton_destruction.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
6_singleton_destruction : $(BUILD_DIR)/6_singleton_destruction
	$<

$(BUILD_DIR)/6_singleton_destruction_2 : $(SRC_DIR)/6_singleton_destruction_2.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
6_singleton_destruction_2 : $(BUILD_DIR)/6_singleton_destruction_2
	$<


$(BUILD_DIR)/7_singleton_multithread_issue : $(SRC_DIR)/7_singleton_multithread_issue.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
7_singleton_multithread_issue : $(BUILD_DIR)/7_singleton_multithread_issue
	$<

$(BUILD_DIR)/7_singleton_multithread_sol : $(SRC_DIR)/7_singleton_multithread_sol.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
7_singleton_multithread_sol : $(BUILD_DIR)/7_singleton_multithread_sol
	$<

$(BUILD_DIR)/7_singleton_multithread_sol_dclp : $(SRC_DIR)/7_singleton_multithread_sol_dclp.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
7_singleton_multithread_sol_dclp : $(BUILD_DIR)/7_singleton_multithread_sol_dclp
	$<

$(BUILD_DIR)/8_using_callonce : $(SRC_DIR)/8_using_callonce.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
8_using_callonce : $(BUILD_DIR)/8_using_callonce
	$<

$(BUILD_DIR)/9_CRTP : $(SRC_DIR)/9_CRTP.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
9_CRTP : $(BUILD_DIR)/9_CRTP
	$<

$(BUILD_DIR)/10_eg_clock : $(SRC_DIR)/10_eg_clock.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
10_eg_clock : $(BUILD_DIR)/10_eg_clock
	$<

$(BUILD_DIR)/10_eg_clock_monostate : $(SRC_DIR)/10_eg_clock_monostate.cpp $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(BOOST_LIB) $(GTEST_LIB) -o $@ $<
10_eg_clock_monostate : $(BUILD_DIR)/10_eg_clock_monostate
	$<



clean :
	rm -rf build

.PHONY : clean
