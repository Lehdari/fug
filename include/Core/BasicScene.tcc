template <typename... T_SceneComponents>
EId BasicScene<T_SceneComponents...>::_entityId;

template <typename... T_SceneComponents>
std::vector<typename BasicScene<T_SceneComponents...>::Entity>
    BasicScene<T_SceneComponents...>::_entities;

template <typename... T_SceneComponents>
std::tuple<std::vector<T_SceneComponents>&...>
    BasicScene<T_SceneComponents...>::_components =
        std::tie(BasicScene<T_SceneComponents...>::accessComponents<T_SceneComponents>()...);


template <typename... T_SceneComponents>
EId BasicScene<T_SceneComponents...>::addEntity(void)
{
    _entities.emplace_back(++_entityId);

    return _entityId;
}

template <typename... T_SceneComponents>
template <typename... T_Components>
EId BasicScene<T_SceneComponents...>::addEntity(T_Components&&... components)
{
    _entities.emplace_back(++_entityId);
    addComponents(std::forward<T_Components>(components)...);

    return _entityId;
}

template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::removeEntity(const EntityId& id)
{
    auto it = _entities.begin();
    findEntity(id, it);
    if (it == _entities.end())
        return;

    removeComponents(it-_entities.begin());

    _entities.erase(it);
}

template <typename... T_SceneComponents>
template <typename T_Visitor, typename... T_Components>
void BasicScene<T_SceneComponents...>::accept(Visitor<T_Visitor, T_Components...>& visitor)
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
template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::print(void) {
    for (auto it = _entities.begin(); it<_entities.end(); ++it)
        std::cout << "Id: " << it->id << std::endl;
}
#endif


template <typename... T_SceneComponents>
int BasicScene<T_SceneComponents...>::findEntity(const EId& entityId, EntityIterator& it, const EntityIterator& endIt)
{
    if (it->id == entityId)
        return 0;

    for (++it; it<endIt; ++it) {
        if (it->id == entityId)
            return 0;
    }
    return 1;
}

template <typename... T_SceneComponents>
template <typename T_Component>
std::vector<T_Component>& BasicScene<T_SceneComponents...>::accessComponents(void)
{
    static std::vector<T_Component> v;
    return v;
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene<T_SceneComponents...>::addComponents(T_FirstComponent&& firstComponent,
                                                     T_SecondComponent&& secondComponent,
                                                     T_Components&&... restComponents)
{
    auto& v = accessComponents<T_FirstComponent>();//std::get<std::vector<T_FirstComponent>&>(_components);
    v.push_back(std::forward<T_FirstComponent>(firstComponent));
    v.back()._entityId = _entityId;
    addComponents<T_SecondComponent, T_Components...>(std::forward<T_SecondComponent>(secondComponent),
                                                      std::forward<T_Components>(restComponents)...);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::addComponents(T_Component&& component)
{
    auto& v = accessComponents<T_Component>();//std::get<std::vector<T_FirstComponent>&>(_components);
    v.push_back(std::forward<T_Component>(component));
    v.back()._entityId = _entityId;
}

template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::removeComponents(uint64_t pos)
{
    removeComponents<T_SceneComponents...>(pos);
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene<T_SceneComponents...>::removeComponents(uint64_t pos)
{
    auto& v = std::get<std::vector<T_FirstComponent>&>(_components);
    v.erase(v.begin()+pos);
    removeComponents<T_SecondComponent, T_Components...>(pos);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::removeComponents(uint64_t pos)
{
    auto& v = std::get<std::vector<T_Component>&>(_components);
    v.erase(v.begin()+pos);
}

template <typename... T_SceneComponents>
template <typename... T_Components>
std::tuple<std::vector<T_Components>&...> BasicScene<T_SceneComponents...>::accessCollection(void)
{
    return std::tie(accessComponents<T_Components>()...);
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene<T_SceneComponents...>::initIterators(std::vector<T_FirstComponent>& firstVector,
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

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::initIterators(std::vector<T_Component>& vector,
                               CIter<T_Component>& iter)
{
    iter = vector.begin();
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
bool BasicScene<T_SceneComponents...>::iterate(
    std::vector<T_FirstComponent>& firstVector,
    std::vector<T_SecondComponent>& secondVector,
    std::vector<T_Components>&... restVectors,
    CIter<T_FirstComponent>& firstIter,
    CIter<T_SecondComponent>& secondIter,
    CIter<T_Components>&... restIters,
    EId& maxId)
{
    for (;maxId > firstIter->_entityId && firstIter != firstVector.end(); ++firstIter);
    maxId = firstIter->_entityId;

    if (firstIter == firstVector.end() || !iterate<T_SecondComponent, T_Components...>
        (secondVector, restVectors..., secondIter, restIters..., maxId))
        return false;

    for (;maxId > firstIter->_entityId && firstIter != firstVector.end();) {
        for (;maxId > firstIter->_entityId && firstIter != firstVector.end(); ++firstIter);
        maxId = firstIter->_entityId;

        if (firstIter == firstVector.end() || !iterate<T_SecondComponent, T_Components...>
            (secondVector, restVectors..., secondIter, restIters..., maxId))
            return false;
    }

    return true;
}

template <typename... T_SceneComponents>
template <typename T_Component>
bool BasicScene<T_SceneComponents...>::iterate(
    std::vector<T_Component>& vector,
    CIter<T_Component>& iter,
    EId& maxId)
{
    for (;maxId > iter->_entityId && iter != vector.end(); ++iter);
    maxId = iter->_entityId;
    if (iter == vector.end())
        return false;
    return true;
}
