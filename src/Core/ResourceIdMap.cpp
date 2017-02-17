#include <cstdint>

#include "Core/ResourceIdMap.hpp"

uint64_t fug::ResourceIdMap::getId(const std::string& resourceName)
{
    /* TODO: Not thread-safe */
    auto idItr = _ids.find(resourceName);
    uint64_t id;

    if (idItr == _ids.end()) {
        _ids.insert(std::make_pair(resourceName, _nextId));
        return _nextId++;
    }
    return idItr->second;
}
