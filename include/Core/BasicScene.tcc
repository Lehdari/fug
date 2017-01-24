EId BasicScene::_entityId;

std::vector<typename BasicScene::Entity>
    BasicScene::_entities;

EId BasicScene::addEntity(void)
{
    _entities.emplace_back(++_entityId);

    return _entityId;
}

template <typename... T_Components>
EId BasicScene::addEntity(T_Components&&... components)
{
    _entities.emplace_back(++_entityId);
    addComponents(std::forward<T_Components>(components)...);

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

template <typename T_Visitor, typename... T_Components>
void BasicScene::accept(Visitor<T_Visitor, T_Components...>& visitor)
{
    static auto collection = accessCollection<T_Components...>();

    std::tuple<CIter<T_Components>...> iters;

    initIterators<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                   std::get<CIter<T_Components>>(iters)...);

    auto entityId = EId();
    ++entityId;
    if (!iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                  std::get<CIter<T_Components>>(iters)...,
                                  entityId))
        return;

    visitor(*std::get<CIter<T_Components>>(iters)...);

    while(iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                   ++std::get<CIter<T_Components>>(iters)...,
                                   entityId)) {
        visitor(*std::get<CIter<T_Components>>(iters)...);
    }
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

template <typename T_Component>
std::vector<T_Component>& BasicScene::accessComponents(void)
{
    static std::vector<T_Component> v;
    return v;
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene::addComponents(T_FirstComponent&& firstComponent,
                               T_SecondComponent&& secondComponent,
                               T_Components&&... restComponents)
{
    auto& v = accessComponents<T_FirstComponent>();
    v.push_back(std::forward<T_FirstComponent>(firstComponent));
    v.back()._entityId = _entityId;
    addComponents<T_SecondComponent, T_Components...>
        (std::forward<T_SecondComponent>(secondComponent),
         std::forward<T_Components>(restComponents)...);
}

template <typename T_Component>
void BasicScene::addComponents(T_Component&& component)
{
    auto& v = accessComponents<T_Component>();
    v.push_back(std::forward<T_Component>(component));
    v.back()._entityId = _entityId;
}

void BasicScene::removeComponents(uint64_t pos)
{
    removeComponents(pos);
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene::removeComponents(uint64_t pos)
{
    auto& v = accessComponents<T_FirstComponent>();
    v.erase(v.begin()+pos);
    removeComponents<T_SecondComponent, T_Components...>(pos);
}

template <typename T_Component>
void BasicScene::removeComponents(uint64_t pos)
{
    auto& v = accessComponents<T_Component>();
    v.erase(v.begin()+pos);
}

template <typename... T_Components>
std::tuple<std::vector<T_Components>&...> BasicScene::accessCollection(void)
{
    return std::tie(accessComponents<T_Components>()...);
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene::initIterators(std::vector<T_FirstComponent>& firstVector,
                                           std::vector<T_SecondComponent>& secondVector,
                                           std::vector<T_Components>&... restVectors,
                                           CIter<T_FirstComponent>& firstIter,
                                           CIter<T_SecondComponent>& secondIter,
                                           CIter<T_Components>&... restIters)
{
    firstIter = firstVector.begin();
    initIterators<T_SecondComponent, T_Components...>(secondVector, restVectors...,
                                                      secondIter, restIters...);
}

template <typename T_Component>
void BasicScene::initIterators(std::vector<T_Component>& vector,
                               CIter<T_Component>& iter)
{
    iter = vector.begin();
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
bool BasicScene::iterate(std::vector<T_FirstComponent>& firstVector,
                         std::vector<T_SecondComponent>& secondVector,
                         std::vector<T_Components>&... restVectors,
                         CIter<T_FirstComponent>& firstIter,
                         CIter<T_SecondComponent>& secondIter,
                         CIter<T_Components>&... restIters,
                         EId& maxId)
{
    for (;firstIter != firstVector.end() && maxId > firstIter->_entityId; ++firstIter);
    if (firstIter != firstVector.end())
        maxId = firstIter->_entityId;

    if (firstIter == firstVector.end() || !iterate<T_SecondComponent, T_Components...>
        (secondVector, restVectors..., secondIter, restIters..., maxId))
        return false;

    for (;firstIter != firstVector.end() && maxId > firstIter->_entityId;) {
        for (;firstIter != firstVector.end() && maxId > firstIter->_entityId; ++firstIter);
        if (firstIter != firstVector.end())
            maxId = firstIter->_entityId;

        if (firstIter == firstVector.end() || !iterate<T_SecondComponent, T_Components...>
            (secondVector, restVectors..., secondIter, restIters..., maxId))
            return false;
    }

    return true;
}

template <typename T_Component>
bool BasicScene::iterate(std::vector<T_Component>& vector,
                         CIter<T_Component>& iter,
                         EId& maxId)
{
    for (;iter != vector.end() && maxId > iter->_entityId; ++iter);

    if (iter != vector.end())
        maxId = iter->_entityId;
    else
        return false;
    return true;
}


