#include <functional>

#include "Core/Log.hpp"
#include "Core/ComponentMap.hpp"


using namespace fug;


ComponentMap& ComponentMap::instance(void)
{
    static ComponentMap ComponentMap;
    return ComponentMap;
}
/*
void ComponentMap::addComponentAddFunction(
    const std::string& componentName,
    ComponentMap::AddFunction func)
{
    FUG_LOG(LogLevel::Debug)("Registering component add function: %s\n",
                              componentName.c_str());
    _addFunctionMap.insert(std::make_pair(componentName, func));
}
*/
ComponentMap::AddFunctionJson ComponentMap::getComponentAddFunction(const std::string& componentName)
{
    auto iter = _addFunctionMap.find(componentName);

    if (iter == _addFunctionMap.end()) {
        FUG_LOG(LogLevel::Error)("ComponentMap: Could not find component add function for: %s\n",
                                 componentName.c_str());
        throw;
    }

    return iter->second;
}

void ComponentMap::addComponent(const std::string& componentName, const ComponentTypeId& typeId) {
    _addFunctionMap[componentName](typeId);
}

void ComponentMap::addComponentType(const ComponentTypeId& typeId, const json& json)
{
    std::string type = json["type"];
    _addTypeFunctionMap[type](typeId, json);
}
