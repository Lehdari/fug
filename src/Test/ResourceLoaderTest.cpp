#include "Test/UnitTests.hpp"

#include "Engine/ResourceLoader.hpp"

#include <iostream>


using namespace fug;


FUG_UNIT_TEST(resourceLoaderTest) {
    std::cout << "Testing ResourceLoader\n\n";

    ResourceLoader resourceLoader("resources.stfu");
    resourceLoader.load();
}
