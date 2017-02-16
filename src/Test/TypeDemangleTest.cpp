#include "Test/UnitTests.hpp"

#include "Core/Utility.hpp"

static int func1(int a);
static void* func2(std::pair<char, int> p);

/* The demangling depends on the C++ ABI which is OS-dependent. */
#if defined(__GNU_LIBRARY__) && defined(__linux__)

FUG_UNIT_TEST(demangleTest)
{
    float f;

    FUG_TEST(fug::util::str<int>() == "int");
    FUG_TEST(fug::util::str<decltype(f)>() == "float");

    FUG_TEST(fug::util::str<decltype(func1)>() == "int (int)");
    FUG_TEST(fug::util::str<decltype(func2)>() ==
             "void* (std::pair<char, int>)");
    FUG_TEST((fug::util::str<std::pair<int, float>>()) ==
             "std::pair<int, float>");
}

#endif
