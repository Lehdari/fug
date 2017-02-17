#ifndef FUG_RESOURCE_ID_MAP_HPP
#define FUG_RESOURCE_ID_MAP_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

#define FUG_RESOURCE_ID_MAP fug::ResourceIdMap::instance()

namespace fug {
    class ResourceIdMap {
    public:
        uint64_t getId(const std::string& resourceName);
        static ResourceIdMap& instance(void)
        {
            static ResourceIdMap resourceIdMap;
            return resourceIdMap;
        }
    private:
        std::unordered_map<std::string, uint64_t> _ids;
        uint64_t _nextId = 0;
    };
};

#endif // FUG_RESOURCE_ID_MAP_HPP
