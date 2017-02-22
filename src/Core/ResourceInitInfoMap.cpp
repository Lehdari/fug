#include <functional>

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
    /*
     * TODO: Implement a proper logging system with variable levels of
     * verbosity
     */
#if 0
     fprintf(stderr, "Registering initInfo for: %s\n",
             initInfoName.c_str());
#endif
    _map.insert(std::make_pair(initInfoName, func));
}

ResourceInitInfoMap::T_InfoFunc
    ResourceInitInfoMap::getInitFunc(const std::string& initInfoName)
{
    auto iter = _map.find(initInfoName);

    if (iter == _map.end()) {
        fprintf(stderr,
                "ResourceInitInfoMap: Could not find initInfo entry for: %s\n",
                initInfoName.c_str());
        throw;
    }

    return iter->second;
}

