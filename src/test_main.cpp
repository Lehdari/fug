#include "Core/Macros.hpp"
#include "Test/UnitTests.hpp"

using namespace fug;

int main(int argc, char *argv[])
{
    if (argc == 1) {
        FUG_TESTER.run();
    } else {
        for (int i = 1; i < argc; ++i)
            FUG_TESTER.run(argv[i], true);
    }

    return 0;
}
