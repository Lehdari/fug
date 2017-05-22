#include "Engine/EntityFactory.hpp"
#include "Core/Log.hpp"

#include <fstream>


using namespace fug;
using namespace nlohmann;


EntityFactory::EntityFactory(const std::string& entityTypesFileName) {
    std::ifstream f(std::string(FUG_RES_DIRECTORY) + entityTypesFileName);
    f >> _entityTypesJson;
}

void EntityFactory::addEntity(const json& entity) {
    std::string entityName = entity["name"];
    FUG_LOG(LogLevel::Debug)("Adding new entity from JSON with name \"%s\"\n",
                             entityName.c_str());

    FUG_SCENE.addEntity();
    for (auto& component : entity["components"]) {
        std::string type = component["type"];
        FUG_COMPONENT_MAP.getComponentAddFunction(type)(component);
    }
}

void EntityFactory::addEntity(const EntityTypeId& typeId) {
    FUG_LOG(LogLevel::Debug)("Adding new entity from with type id \"%s\"\n",
                             typeId.c_str());

    FUG_SCENE.addEntity();
    for (auto& componentTypeId : _entityComponents[typeId]) {
        FUG_LOG(LogLevel::Debug)("Adding component with type id \"%s\"\n",
                                 componentTypeId.c_str());
        FUG_COMPONENT_MAP.addComponent(componentTypeId, typeId);
    }
}

void EntityFactory::addEntityType(const EntityTypeId& typeId, const json& entity) {
    std::string entityName = entity["name"];
    FUG_LOG(LogLevel::Debug)("Adding new entity type from JSON with name \"%s\"\n",
                             entityName.c_str());

    for (auto& component : entity["components"]) {
        std::string type = component["type"];
        FUG_LOG(LogLevel::Debug)("Component type: %s\n",
                                 type.c_str());
        _entityComponents[typeId].push_back(type);
        FUG_COMPONENT_MAP.addComponentType(typeId, component);
    }
}

void EntityFactory::load(void) {
    FUG_LOG(LogLevel::Debug)("Loading entity types\n");

    for (auto& entity : _entityTypesJson["Entities"]) {
        addEntityType(entity["name"], entity);
    }
}
