#ifndef FUG_RESOURCE_INIT_INFO_MAP_HPP
#define FUG_RESOURCE_INIT_INFO_MAP_HPP

#include <functional>
#include <unordered_map>

#include "Core/ResourceIdMap.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/Types.hpp"

#include "json/json.hpp"


#define FUG_RESOURCE_INIT_INFO_MAP fug::ResourceInitInfoMap::instance()

#define FUG_RESOURCE_INITINFO_INIT(T_Resource, T_InitInfo) \
    static void initInitInfo(const json& json, T_InitInfo& initInfo); \
    static fug::ResourceInitInfoMapEntry<T_Resource, T_InitInfo> \
        resourceInitInfoMap_##T_InitInfo(#T_InitInfo); \
    static void initInitInfo(const json& json, T_InitInfo& initInfo) \

using namespace nlohmann;

namespace fug {

    template <typename T_InitInfo>
    static void initInitInfo(const json& json, T_InitInfo& initInfo);

    class ResourceInitInfoMap {
    public:
        using T_InfoFunc = std::function<void(const json&)>;
        void addInitInfo(std::string initInfoName, T_InfoFunc func);

        T_InfoFunc getInitFunc( const std::string& initInfoName);

        static ResourceInitInfoMap& instance(void);

    private:
        std::unordered_map<std::string, T_InfoFunc> _map;
    };

    template <typename T_Resource, typename T_InitInfo>
    class ResourceInitInfoMapEntry {
    public:
        ResourceInitInfoMapEntry(const std::string& initInfoName)
        {
            FUG_RESOURCE_INIT_INFO_MAP.addInitInfo(initInfoName, addInitInfo);
        }

    private:
        static void addInitInfo(const json& json)
        {
            T_InitInfo initInfo;
            std::vector<RId> initResources;
            std::vector<RId> depResources;

            for (auto& initResource: json["initResources"])
                initResources.push_back(FUG_RESOURCE_ID_MAP.getId(initResource));
            for (auto& depResource: json["depResources"])
                depResources.push_back(FUG_RESOURCE_ID_MAP.getId(depResource));

            initInitInfo(json["initInfo"], initInfo);

            auto resId = FUG_RESOURCE_ID_MAP.getId(json["id"]);
            FUG_RESOURCE_MANAGER.addResourceInfo<T_Resource, T_InitInfo>
                (resId, initInfo, initResources, depResources);
        }
    };

}


#endif // FUG_RESOURCE_INIT_INFO_MAP_HPP
