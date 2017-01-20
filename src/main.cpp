#ifdef FUG_UNIT_TEST == 0
    #include "Test/UnitTests.hpp"

    using namespace fug;

#else
    #include "GameJam2017/GameJam2017.hpp"

    using namespace fgj;
#endif


int main(void) {

    #ifdef FUG_UNIT_TEST == 0
    unitTest();
    #else
    return gameJam2017();
    #endif

    return 0;
}
