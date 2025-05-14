#include <gtest/gtest.h>
#include "ioda_attribute/ioda_attribute.hpp"

TEST(IodaAttribute, IodaAttribute) {
    auto iodaAttribute = IodaAttribute("eastward_wind");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}gi
