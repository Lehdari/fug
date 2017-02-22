#ifndef FUG_UNIT_TESTS_HPP
#define FUG_UNIT_TESTS_HPP

#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Core/Macros.hpp"

#define FUG_UNIT_TEST(testName) \
    static void testName##TestFunc(const fug::UnitTest& unitTest); \
    static fug::UnitTest test##testName(#testName, testName##TestFunc); \
    static void testName##TestFunc(const fug::UnitTest& unitTest)

/* XXX: Legacy, remove once not needed */
#define FUG_TEST_CASE(...)

#define FUG_TEST(testExpr) \
    do { \
        if (!(testExpr)) \
            unitTest.fail(__LINE__, #testExpr); \
    } while (0)

#define FUG_TEST_MSG(testExpr, msg) \
    do { \
        if (!(testExpr)) \
            unitTest.fail(__LINE__, (msg)); \
    } while (0)

#define FUG_TEST_EQ(testExpr, corrExpr) \
    do { \
        std::ostringstream err; \
        err << testExpr << " == " << corrExpr; \
        FUG_TEST_MSG((testExpr) == (corrExpr), err.str()); \
    } while (0)


#define FUG_TESTER fug::Tester::instance()

namespace fug {

    class UnitTest {
    public:
        using T_TestFunc = std::function<void(const UnitTest& test)>;
        UnitTest(const std::string& testName, T_TestFunc testFunc);
        void operator()(void);
        void fail(unsigned line, const std::string& msg) const;
    private:
        std::function<void(const UnitTest& test)> _testFunc;
        const std::string _testName;
    };

    class Tester {
    public:
        void addTest(const std::string& testName, const UnitTest& test);
        void run(bool dieOnFail = true);
        void run(const std::string& testName, bool dieOnFail = true);
        void fail(void);
        static Tester& instance(void);
    private:
        std::unordered_map<std::string, UnitTest> _testFuncs;
        void run(std::pair<std::string, UnitTest> test, bool dieOnFail = true);
        bool _dieOnFail;
    };

}


#endif // FUG_UNIT_TESTS_HPP
