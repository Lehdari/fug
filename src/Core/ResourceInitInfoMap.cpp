#include <functional>

#include "Core/Log.hpp"
#include "Core/ResourceInitInfoMap.hpp"

using namespace fug;

ResourceInitInfoMap& ResourceInitInfoMap::instance(void)
{
    static ResourceInitInfoMap resourceInitInfoMap;
    return resourceInitInfoMap;
}

void ResourceInitInfoMap::addInitInfo(std::string initInfoName,
                                      ResourceInitInfoMap::T_InfoFunc func)
{
     FUG_LOG(LogLevel::Debug)("Registering initInfo for: %s\n",
                              initInfoName.c_str());
    _map.insert(std::make_pair(initInfoName, func));
}

ResourceInitInfoMap::T_InfoFunc
    ResourceInitInfoMap::getInitFunc(const std::string& initInfoName)
{
    auto iter = _map.find(initInfoName);

    if (iter == _map.end()) {
        FUG_LOG(LogLevel::Error)("ResourceInitInfoMap: Could not find initInfo entry for: %s\n",
                                 initInfoName.c_str());
        throw;
    }

    return iter->second;
}

