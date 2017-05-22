#ifndef FUG_COMPONENT_MAP_HPP
#define FUG_COMPONENT_MAP_HPP


#include <functional>
#include <unordered_map>

#include "Core/Scene.hpp"
#include "Core/Log.hpp"

#include "json/json.hpp"


#define FUG_COMPONENT_MAP fug::ComponentMap::instance()

#define FUG_COMPONENT_INIT(T_Component) \
    static void initComponent(const json& json, T_Component& component); \
    static fug::ComponentMapEntry<T_Component> \
        ComponentMap_##T_Component(#T_Component); \
    static void initComponent(const json& json, T_Component& component) \


using namespace nlohmann;

namespace fug {

    using ComponentTypeId = std::string;


    template <typename T_Component>
    static void initComponent(const json& json, T_Component& component);

    class ComponentMap {
    public:
        using AddFunctionJson = std::function<void(const json&)>;
        using AddFunction = std::function<void(const ComponentTypeId&)>;
        using AddTypeFunction = std::function<void(const ComponentTypeId&, const json&)>;

        template <typename T_Component>
        friend class ComponentMapEntry;

        static ComponentMap& instance(void);

        //void addComponentAddFunction(const std::string& ComponentName, AddFunction func);
        AddFunctionJson getComponentAddFunction(const std::string& ComponentName);
        void addComponent(const std::string& componentName, const ComponentTypeId& typeId);

        template <typename T_Component>
        void addComponentType(const ComponentTypeId& typeId, const T_Component& component);
        void addComponentType(const ComponentTypeId& typeId, const json& json);

    private:
        std::unordered_map<std::string, AddFunctionJson>        _addFunctionJsonMap;
        std::unordered_map<std::string, AddFunction>            _addFunctionMap;
        std::unordered_map<std::string, AddTypeFunction>    _addTypeFunctionMap;

        //  vector for predefined component states (component types)
        template <typename T_Component>
        std::unordered_map<ComponentTypeId, T_Component>& accessComponentTypes(void);
    };

    template <typename T_Component>
    class ComponentMapEntry {
    public:
        ComponentMapEntry(const std::string& componentName);

    private:
        static void addComponentJson(const json& json);
        static void addComponent(const ComponentTypeId& typeId);
        static void addComponentType(const ComponentTypeId& typeId, const json& json);
    };

    #include "ComponentMap.tcc"

}


#endif // FUG_COMPONENT_MAP_HPP
