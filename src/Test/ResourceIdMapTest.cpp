#include "Test/UnitTests.hpp"

#include "Core/ResourceIdMap.hpp"

FUG_UNIT_TEST(resourceIdMapTest)
{
    auto id0 = FUG_RESOURCE_ID_MAP.getId("resourceIdMapTest_Id_0");
    auto id1 = FUG_RESOURCE_ID_MAP.getId("resourceIdMapTest_Id_1");
    auto id2 = FUG_RESOURCE_ID_MAP.getId("resourceIdMapTest_Id_2");
    FUG_TEST_EQ(id1, id0 + 1);
    FUG_TEST_EQ(id2, id0 + 2);

    auto id00 = FUG_RESOURCE_ID_MAP.getId("resourceIdMapTest_Id_0");
    auto id11 = FUG_RESOURCE_ID_MAP.getId("resourceIdMapTest_Id_1");
    auto id22 = FUG_RESOURCE_ID_MAP.getId("resourceIdMapTest_Id_2");
    FUG_TEST_EQ(id00, id0);
    FUG_TEST_EQ(id11, id1);
    FUG_TEST_EQ(id22, id2);
}
