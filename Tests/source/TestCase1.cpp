//
// Created by dex_y on 12.09.2023.
//
#include <gtest/gtest.h>

#include <Locker/Locker.h>

TEST(ConstructorTests, openTest){
    Locker tmp(15);
    ASSERT_TRUE(tmp.isOpen());
}

TEST(ConstructorTests, closedTest){
    Locker tmp(15, true);
    ASSERT_FALSE(tmp.isOpen());
}

TEST(ConstructorTests,throwTest){
    ASSERT_ANY_THROW(Locker (1e12));
    ASSERT_NO_THROW(Locker (9));
}

TEST(MethodsTest, closeTest){
    Locker tmp(15, false);

    tmp.close();
    ASSERT_FALSE(tmp.isOpen());

    tmp.close();
    ASSERT_FALSE(tmp.isOpen());

}

TEST (MethdsTest, openTest) {
    Locker tmp(15, true);
    ASSERT_FALSE(tmp.open(11));
    ASSERT_FALSE(tmp.isOpen());

    ASSERT_TRUE(tmp.open(15));
    ASSERT_TRUE(tmp.isOpen());

    ASSERT_TRUE(tmp.open(15));
    ASSERT_TRUE(tmp.isOpen());
}