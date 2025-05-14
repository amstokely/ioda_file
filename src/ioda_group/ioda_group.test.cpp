#include <gtest/gtest.h>
#include "ioda_group/ioda_group.hpp"

class IodaGroupFixture : public ::testing::Test {
protected:

    const std::string rootGroupName = "/";
    const std::string v2GroupName = "MetaData";
    const std::string v1VariableName = "eastward_wind@ObsValue";
    const std::string v1V2VariableName = "eastward_wind";
    const std::string v1V2V3VariableName = "windEastward";
    const std::string v1V2GroupName = "ObsValue";
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(IodaGroupFixture, IodaGroup) {
    auto rootGroup = IodaGroup(rootGroupName);
    rootGroup.addGroup(v2GroupName);
    rootGroup.addVariable(v1V2VariableName);
    rootGroup.addVariable(v1VariableName);
    const auto groups = rootGroup.getGroups();
    ASSERT_EQ(rootGroup.getName(), rootGroupName);
    ASSERT_EQ(groups.find(v2GroupName)->second->getName(), v2GroupName);
    ASSERT_EQ(groups.find(v1V2GroupName)->second->getName(), v1V2GroupName);
    ASSERT_EQ(rootGroup.getVariable(v1V2VariableName)->getName(), v1V2V3VariableName);
    ASSERT_EQ(rootGroup.getVariable(v1V2VariableName)->getName(), v1V2V3VariableName);
    ASSERT_EQ(rootGroup.getVariable(v1VariableName)->getName(), v1V2V3VariableName);
    ASSERT_TRUE(rootGroup.hasVariable(v1V2VariableName));
    ASSERT_TRUE(rootGroup.hasVariable(v1VariableName));
    ASSERT_TRUE(rootGroup.hasVariable(v1V2V3VariableName));


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}