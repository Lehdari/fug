#include <functional>

#include "Core/ResourceInitInfoMap.hpp"

void fug::ResourceInitInfoMap::addInitInfo(
    std::string initInfoName,
    std::function<void(const json&)> func)
{
    /*
     * TODO: Implement a proper logging system with variable levels of
     * verbosity
     * fprintf(stderr, "Registering initInfo for: %s\n",
     *         initInfoName.c_str());
     */
    _map.insert(std::make_pair(initInfoName, func));
}



std::function<void(const json&)> fug::ResourceInitInfoMap::getInitFunc(
    const std::string& initInfoName)
{
    auto iter = _map.find(initInfoName);

    if (iter == _map.end()) {
        fprintf(stderr,
                "ResourceInitInfoMap: Could not find initInfo entry for: %s\n",
                initInfoName.c_str());
        throw;
    }

    return _map[initInfoName];
}

fug::ResourceInitInfoMapEntry::ResourceInitInfoMapEntry(
    const std::string& initInfoName,
    std::function<void(const json&)> func)
{
    fug::ResourceInitInfoMap::instance().addInitInfo(initInfoName,
                                                     func);
}

