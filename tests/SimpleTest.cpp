//
// Created by Jens Klimke on 2019-04-25.
//

#include <gtest/gtest.h>
#include <one/lib.h>
#include <two/lib.h>

TEST(SimpleTest, OneTest) {

    EXPECT_TRUE(one());

}

TEST(SimpleTest, TwoTest) {

    EXPECT_FALSE(two());

}