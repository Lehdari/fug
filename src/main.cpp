#include "Test/UnitTests.hpp"


using namespace fug;


int main(void) {

    #ifdef FUG_UNIT_TEST
    unitTest();
    #endif

    return 0;
}
