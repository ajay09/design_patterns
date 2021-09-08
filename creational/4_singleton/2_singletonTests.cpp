#include "2_singleton.hpp"
#include <gtest/gtest.h>

TEST(DatabaseTests, IsSingletontest) {
	auto &db = SingletonDatabase::get();
	auto &db2 = SingletonDatabase::get();
	ASSERT_EQ(1, db.instance_count);
	ASSERT_EQ(1, db2.instance_count);
}

int main(int ac, char* av[]) {
	/*
	All 3 of them should be blocked.
		SingletonDatabase db;  // Constructor is private
		auto db2(db);          // delete Copy-constructor
		auto db3 = db;		   // delete copy-assignment operator
	*/

	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();

	return 0;
}