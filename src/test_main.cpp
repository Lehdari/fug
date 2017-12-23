#include <iostream>
#include <unordered_map>
#include <vector>

#include "Core/Log.hpp"
#include "Core/Macros.hpp"
#include "Test/UnitTests.hpp"

using namespace fug;

int main(int argc, char *argv[])
{

    std::vector<std::string> testNames;

    FUG_LOG.setLogLevel(LogLevel::Error);

    std::string param;
    std::string arg;
    bool isParam = false;

    std::unordered_map<std::string, LogLevel> logLevels = {
        {"Debug", LogLevel::Debug},
        {"Info", LogLevel::Info},
        {"Warn", LogLevel::Warn},
        {"Error", LogLevel::Error}
    };

    /* TODO: This should be a nice generic data-driven thing, but oh well */
    for (int i = 1; i < argc; ++i) {
        if (i < argc)
            arg = std::string(argv[i]);
        if (!isParam) {
            if (arg[0] == '-') {
                isParam = true;
                param = arg;
            } else {
                if (!arg.compare("all"))  {
                    testNames = FUG_TESTER.getTestNames();
                    break;
                }
                testNames.push_back(arg);
            }
        } else {
            if (param == "-v") {
                auto level = logLevels.find(arg);
                if (level == logLevels.end())
                    FUG_LOG(LogLevel::Error)("Invalid commandline parameter %s for: %s\n",
                                             arg.c_str(), param.c_str());
                FUG_LOG.setLogLevel(level->second);
            } else {
                FUG_LOG(LogLevel::Error)("Invalid commandline argument: %s\n",
                                         param.c_str());
                return -1;
            }
            isParam = false;
        }
    }

    if (argc == 1) {
        printf("Usage: %s [-v Debug|Info|Warn|Error] [TEST_NAME] [TEST_NAME] ...\n",
               argv[0]);
        printf("Valid test names are:\n");
        for (const auto &testName: FUG_TESTER.getTestNames())
            printf("\t%s\n", testName.c_str());
        printf("\tall (runs all of the tests above)\n");
        return 0;
    }

    for (const auto& testName: testNames)
        FUG_TESTER.run(testName, true);

    return 0;
}
