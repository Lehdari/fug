#include "Core/BasicScene.hpp"

using namespace fug;

EId BasicScene::_entityId = EId();

std::vector<typename BasicScene::Entity>
    BasicScene::_entities;

EId BasicScene::addEntity(void)
{
    _entities.emplace_back(++_entityId);

    return _entityId;
}

void BasicScene::removeEntity(const EntityId& id)
{
    auto it = _entities.begin();
    findEntity(id, it);
    if (it == _entities.end())
        return;

    removeComponents(it-_entities.begin());

    _entities.erase(it);
}

#ifdef FUG_DEBUG
void BasicScene::print(void) {
    for (auto it = _entities.begin(); it<_entities.end(); ++it)
        std::cout << "Id: " << it->id << std::endl;
}
#endif

int BasicScene::findEntity(const EId& entityId, EntityIterator& it,
                           const EntityIterator& endIt)
{
    if (it->id == entityId)
        return 0;

    for (++it; it<endIt; ++it) {
        if (it->id == entityId)
            return 0;
    }
    return 1;
}

void BasicScene::removeComponents(uint64_t pos)
{
    removeComponents(pos);
}


