#ifndef FUG_UNIT_TESTS_HPP
#define FUG_UNIT_TESTS_HPP

#include <functional>
#include <string>
#include <unordered_map>

#include "Core/Macros.hpp"

#define FUG_UNIT_TEST(testName) \
    static void testName##TestFunc(void); \
    static fug::UnitTest test ##testName(#testName, testName ##TestFunc); \
    static void testName##TestFunc(void)

#define FUG_TESTER fug::Tester::instance()

namespace fug {

    class Tester {
    public:
        void addTest(const std::string& testName,
                     const std::function<void(void)> testFunc);
        void run(void);
        void run(const std::string& testName);
        static Tester& instance(void)
        {
            static Tester tester;
            return tester;
        }
    private:
        std::unordered_map<std::string,
                           std::function<void(void)>> _testFuncs;
        void run(std::pair<std::string, std::function<void(void)>> test);
    };

    class UnitTest {
    public:
        UnitTest(const std::string& testName,
                 const std::function<void(void)> testFunc);
    };

}


#endif // FUG_UNIT_TESTS_HPP
