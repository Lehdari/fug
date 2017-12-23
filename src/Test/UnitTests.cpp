#include "Core/Log.hpp"

#include "Test/UnitTests.hpp"

#include <cstdio>


fug::UnitTest::UnitTest(const std::string& testName,
                        fug::UnitTest::T_TestFunc testFunc) :
    _testFunc(testFunc),
    _testName(testName)
{
    FUG_TESTER.addTest(testName, *this);
}

void fug::UnitTest::operator()(void)
{
    _testFunc(*this);
}

void fug::UnitTest::fail(unsigned line, const std::string& msg) const
{
    FUG_LOG(LogLevel::Error)("Test: \"%s\" failed at: %u, with: \"%s\"\n",
                             _testName.c_str(), line, msg.c_str());
    FUG_TESTER.fail();
}

fug::Tester& fug::Tester::instance(void)
{
    static Tester tester;
    return tester;
}

void fug::Tester::addTest(const std::string& testName,
                          const fug::UnitTest& test)
{
    _testFuncs.insert(std::make_pair(testName, test));
}

void fug::Tester::run(std::pair<std::string, fug::UnitTest> test,
                      bool dieOnFail)
{
    FUG_LOG(LogLevel::Info)("Running test: %s\n", test.first.c_str());
    _dieOnFail = dieOnFail;
    test.second();
}

void fug::Tester::run(bool dieOnFail)
{
    for (const auto& test: _testFuncs)
        run(test, dieOnFail);
}

void fug::Tester::run(const std::string& testName, bool dieOnFail)
{
    auto test = _testFuncs.find(testName);

    if (test == _testFuncs.end())
        FUG_LOG(LogLevel::Error)("Could not find test: \"%s\"\n",
                                 testName.c_str());
    else
        run(*test);
}

void fug::Tester::fail(void)
{
    if (_dieOnFail)
        throw;
}

std::vector<std::string> fug::Tester::getTestNames()
{
    std::vector<std::string> names;

    for (auto &test: _testFuncs)
        names.emplace_back(test.first);

    return names;
}

