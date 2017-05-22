#ifndef FUG_ENTITY_FACTORY_HPP
#define FUG_ENTITY_FACTORY_HPP


#include <string>
#include <unordered_map>
#include <vector>

#include "json/json.hpp"

#include "Core/ComponentMap.hpp"


namespace fug {

    using EntityTypeId = std::string;

    class EntityFactory {
    public:
        EntityFactory(const std::string& entityTypesFileName);

        void addEntity(const nlohmann::json& entity);
        void addEntity(const EntityTypeId& typeId);

        void addEntityType(const EntityTypeId& typeId, const nlohmann::json& entity);

        void load(void);

    private:
        nlohmann::json    _entityTypesJson;

        std::unordered_map<EntityTypeId, std::vector<std::string>>  _entityComponents;
    };

}


#endif  //  FUG_ENTITY_FACTORY_HPP
