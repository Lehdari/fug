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
    for (int i = 1; i < (argc); ++i) {
        if (i < argc)
            arg = std::string(argv[i]);
        if (!isParam) {
            if (arg[0] == '-') {
                isParam = true;
                param = arg;
            } else {
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

    if (testNames.size() == 0) {
        FUG_TESTER.run();
    } else {
        for (const auto& testName: testNames)
            FUG_TESTER.run(testName, true);
    }

    return 0;
}
