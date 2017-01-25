template <typename... T_Components>
EId BasicScene::addEntity(T_Components&&... components)
{
    _entities.emplace_back(++_entityId,
        std::vector<void(BasicScene::*)(const EId&)> {
            &BasicScene::removeComponents<T_Components>...});

    addComponents(std::forward<T_Components>(components)...);

    return _entityId;
}

template <typename T_Visitor, typename... T_Components>
void BasicScene::accept(Visitor<T_Visitor, T_Components...>& visitor)
{
    static auto collection = accessCollection<T_Components...>();

    std::tuple<ComponentIter<T_Components>...> iters;

    initIterators<T_Components...>(std::get<ComponentVector<T_Components>&>(collection)...,
                                   std::get<ComponentIter<T_Components>>(iters)...);

    auto entityId = EId();
    ++entityId;
    if (!iterate<T_Components...>(std::get<ComponentVector<T_Components>&>(collection)...,
                                  std::get<ComponentIter<T_Components>>(iters)...,
                                  entityId))
        return;

    visitor(std::get<ComponentIter<T_Components>>(iters)->component...);

    while(iterate<T_Components...>(std::get<ComponentVector<T_Components>&>(collection)...,
                                   ++std::get<ComponentIter<T_Components>>(iters)...,
                                   entityId)) {
        visitor(std::get<ComponentIter<T_Components>>(iters)->component...);
    }
}


template <typename T_Component>
BasicScene::ComponentVector<T_Component>& BasicScene::accessComponents(void)
{
    static ComponentVector<T_Component> v;
    return v;
}

template <typename... T_Components>
BasicScene::ComponentCollection<T_Components...> BasicScene::accessCollection(void)
{
    return std::tie(accessComponents<T_Components>()...);
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene::addComponents(
   T_FirstComponent&& firstComponent,
   T_SecondComponent&& secondComponent,
   T_Components&&... restComponents)
{
    auto& v = accessComponents<T_FirstComponent>();
    v.emplace_back(ComponentWrapper<T_FirstComponent>{
        _entityId, std::forward<T_FirstComponent>(firstComponent)});

    addComponents<T_SecondComponent, T_Components...>(
        std::forward<T_SecondComponent>(secondComponent),
        std::forward<T_Components>(restComponents)...);
}

template <typename T_Component>
void BasicScene::addComponents(T_Component&& component)
{
    auto& v = accessComponents<T_Component>();
    v.emplace_back(ComponentWrapper<T_Component>{
        _entityId, std::forward<T_Component>(component)});
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene::removeComponents(const EId& entityId)
{
    auto& v = accessComponents<T_FirstComponent>();
    v.erase(
    std::remove_if(v.begin(), v.end(),
        [&entityId](const auto& c) { return c.entityId == entityId; }),
    v.end());
    removeComponents<T_SecondComponent, T_Components...>(entityId);
}

template <typename T_Component>
void BasicScene::removeComponents(const EId& entityId)
{
    auto& v = accessComponents<T_Component>();
    v.erase(
    std::remove_if(v.begin(), v.end(),
        [&entityId](const auto& c) { return c.entityId == entityId; }),
    v.end());
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene::initIterators(
    ComponentVector<T_FirstComponent>& firstVector,
    ComponentVector<T_SecondComponent>& secondVector,
    ComponentVector<T_Components>&... restVectors,
    ComponentIter<T_FirstComponent>& firstIter,
    ComponentIter<T_SecondComponent>& secondIter,
    ComponentIter<T_Components>&... restIters)
{
    firstIter = firstVector.begin();
    initIterators<T_SecondComponent, T_Components...>(secondVector, restVectors...,
                                                      secondIter, restIters...);
}

template <typename T_Component>
void BasicScene::initIterators(ComponentVector<T_Component>& vector,
                               ComponentIter<T_Component>& iter)
{
    iter = vector.begin();
}

template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
bool BasicScene::iterate(
    ComponentVector<T_FirstComponent>& firstVector,
    ComponentVector<T_SecondComponent>& secondVector,
    ComponentVector<T_Components>&... restVectors,
    ComponentIter<T_FirstComponent>& firstIter,
    ComponentIter<T_SecondComponent>& secondIter,
    ComponentIter<T_Components>&... restIters,
    EId& maxId)
{
    for (;firstIter != firstVector.end() && maxId > firstIter->entityId; ++firstIter);
    if (firstIter != firstVector.end())
        maxId = firstIter->entityId;

    if (firstIter == firstVector.end() || !iterate<T_SecondComponent, T_Components...>
        (secondVector, restVectors..., secondIter, restIters..., maxId))
        return false;

    for (;firstIter != firstVector.end() && maxId > firstIter->entityId;) {
        for (;firstIter != firstVector.end() && maxId > firstIter->entityId; ++firstIter);
        if (firstIter != firstVector.end())
            maxId = firstIter->entityId;

        if (firstIter == firstVector.end() || !iterate<T_SecondComponent, T_Components...>
            (secondVector, restVectors..., secondIter, restIters..., maxId))
            return false;
    }

    return true;
}

template <typename T_Component>
bool BasicScene::iterate(
    ComponentVector<T_Component>& vector,
    ComponentIter<T_Component>& iter,
    EId& maxId)
{
    for (;iter != vector.end() && maxId > iter->entityId; ++iter);


    if (iter != vector.end())
        maxId = iter->entityId;
    else
        return false;
    return true;
}

