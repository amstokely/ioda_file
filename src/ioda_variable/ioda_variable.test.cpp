#include <gtest/gtest.h>
#include "ioda_variable/ioda_variable.hpp"

TEST(IodaVariable, IodaVariable) {
    auto iodaVariable = IodaVariable("eastward_wind");
    EXPECT_EQ(iodaVariable.getName(), "windEastward");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}