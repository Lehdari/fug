template <typename... T_SceneComponents>
NId BasicScene<T_SceneComponents...>::_nodeId;

template <typename... T_SceneComponents>
std::vector<typename BasicScene<T_SceneComponents...>::Node>
    BasicScene<T_SceneComponents...>::_nodes;

template <typename... T_SceneComponents>
std::tuple<std::vector<T_SceneComponents>&...>
    BasicScene<T_SceneComponents...>::_components =
        std::tie(BasicScene<T_SceneComponents...>::accessComponents<T_SceneComponents>()...);


template <typename... T_SceneComponents>
NId BasicScene<T_SceneComponents...>::addNode(void)
{
    _nodes.emplace_back(++_nodeId);
    addComponents(_nodes.size()-1);

    return _nodeId;
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent, typename... T_Components>
NId BasicScene<T_SceneComponents...>::addNode(T_FirstComponent&& firstComponent,
                                              T_Components&&... components)
{
    _nodes.emplace_back(++_nodeId);
    addComponents(_nodes.size()-1);
    setComponents(_nodes.size()-1,
                  std::forward<T_FirstComponent>(firstComponent),
                  std::forward<T_Components>(components)...);

    return _nodeId;
}

template <typename... T_SceneComponents>
NId BasicScene<T_SceneComponents...>::addChildNode(const NId& parent)
{
    auto parentIt = _nodes.begin();
    findNode(parent, parentIt, _nodes.end());
    if (parentIt == _nodes.end())
        return NId();

    auto childIt = parentIt + parentIt->size;
    increaseNodeSize(parentIt);
    parentIt->children.push_back(++_nodeId);

    addComponents(childIt-_nodes.begin());

    _nodes.emplace(childIt, _nodeId, parentIt->id);

    return _nodeId;
}

template <typename... T_SceneComponents>
template <typename... T_Components>
NId BasicScene<T_SceneComponents...>::addChildNode(const NId& parent, T_Components&&... components)
{
    auto parentIt = _nodes.begin();
    findNode(parent, parentIt, _nodes.end());
    if (parentIt == _nodes.end())
        return NId();

    auto childIt = parentIt + parentIt->size;
    increaseNodeSize(parentIt);
    parentIt->children.push_back(++_nodeId);

    uint64_t pos = childIt-_nodes.begin();
    addComponents(pos);
    setComponents(pos, std::forward<T_Components>(components)...);

    _nodes.emplace(childIt, _nodeId, parentIt->id);

    return _nodeId;
}

template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::removeNode(const NodeId& id)
{
    auto it = _nodes.begin();
    findNode(id, it);
    if (it == _nodes.end())
        return;

    auto nodeSize = it->size;

    removeComponents(it-_nodes.begin(), it-_nodes.begin()+nodeSize);

    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    decreaseNodeSize(parentIt, nodeSize);

    for (auto pcIt = parentIt->children.begin(); pcIt != parentIt->children.end(); ++pcIt)
        if (*pcIt == id) {
            parentIt->children.erase(pcIt);
            break;
        }

    _nodes.erase(it, it+nodeSize);
}

template <typename... T_SceneComponents>
template <typename T_Visitor, typename... T_Components>
void BasicScene<T_SceneComponents...>::accept(Visitor<T_Visitor, T_Components...>& visitor)
{
    static auto collection = accessCollection<T_Components...>();

    std::tuple<CIter<T_Components>...> iters;

    initIterators<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                   std::get<CIter<T_Components>>(iters)...);

    std::unordered_map<CId, uint64_t> nIterations;
    uint64_t maxIterations = 0;

    NodeIterator nodeIt = _nodes.begin();

    if (!iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                  std::get<CIter<T_Components>>(iters)...,
                                  nIterations, maxIterations))
        return;
    nodeIt += maxIterations;
    for (auto& nit : nIterations)
        nit.second = 0;

    if (!visitor(*std::get<CIter<T_Components>>(iters)...))
        maxIterations = nodeIt->size;
    else
        maxIterations = 1;


    while(iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                   std::get<CIter<T_Components>>(iters)...,
                                   nIterations, maxIterations)) {
        nodeIt += maxIterations;
        for (auto& nit : nIterations)
            nit.second = 0;

        if (!visitor(*std::get<CIter<T_Components>>(iters)...))
            maxIterations = nodeIt->size;
        else
            maxIterations = 1;
    }
}

#ifdef FUG_DEBUG
template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::print(const NodeIterator& beginIt, const NodeIterator& endIt, uint32_t level) {
    NodeIterator it = beginIt;
    for (;it<endIt;) {
        for (auto i=0u; i<level; ++i)
            std::cout << "  ";
        std::cout << "Id: " << it->id << ", Size: " << it->size;

        if (it->children.size() > 0) {
            std::cout << ", Children: ";
            for (auto& childId : it->children)
                std::cout << childId << ", ";
            std::cout << std::endl;

            auto endIt2 = it+it->size;
            print(++it, endIt2, level+1);
            it = endIt2;
        }
        else {
            std::cout << std::endl;
            ++it;
        }
    }

    if (level == 0) {
        for (auto& c : accessComponents<TestComponent1>())
            printf("%llu a:%d b:%d\n", c._nodeId, c.a, c.b);
    }
}
#endif


template <typename... T_SceneComponents>
int BasicScene<T_SceneComponents...>::findNode(const NId& nodeId, NodeIterator& it, const NodeIterator& endIt)
{
    if (it->id == nodeId)
        return 0;

    for (++it; it<endIt; ++it) {
        if (it->id == nodeId)
            return 0;
    }
    return 1;
}

template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::increaseNodeSize(NodeIterator& it)
{
    ++it->size;
    if (it->parent == 0)
        return;
    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    increaseNodeSize(parentIt);
}

template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::decreaseNodeSize(NodeIterator& it, uint64_t amount)
{
    it->size-=amount;
    if (it->parent == 0)
        return;
    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    decreaseNodeSize(parentIt, amount);
}

template <typename... T_SceneComponents>
template <typename T_Component>
std::vector<T_Component>& BasicScene<T_SceneComponents...>::accessComponents(void)
{
    static std::vector<T_Component> v;
    return v;
}

template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::addComponents(uint64_t pos)
{
    addComponents<T_SceneComponents...>(pos);
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene<T_SceneComponents...>::addComponents(uint64_t pos)
{
    auto& v = std::get<std::vector<T_FirstComponent>&>(_components);
    auto nIt = v.insert(v.begin()+pos, T_FirstComponent());
    nIt->_nodeId = NId();
    addComponents<T_SecondComponent, T_Components...>(pos);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::addComponents(uint64_t pos)
{
    auto& v = std::get<std::vector<T_Component>&>(_components);
    auto nIt = v.insert(v.begin()+pos, T_Component());
    nIt->_nodeId = NId();
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent, typename... T_Components>
void BasicScene<T_SceneComponents...>::setComponents(uint64_t pos,
                                                     T_FirstComponent&& firstComponent,
                                                     T_Components&&... components)
{
    auto& c = *(accessComponents<T_FirstComponent>().begin() + pos);
    c = std::forward<T_FirstComponent>(firstComponent);
    c._nodeId = _nodeId;

    //  set rest of the components
    setComponents(pos, std::forward<T_Components>(components)...);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::setComponents(uint64_t pos, T_Component&& component)
{
    auto& c = *(accessComponents<T_Component>().begin() + pos);
    c = std::forward<T_Component>(component);
    c._nodeId = _nodeId;
}

template <typename... T_SceneComponents>
void BasicScene<T_SceneComponents...>::removeComponents(uint64_t begin, uint64_t end)
{
    removeComponents<T_SceneComponents...>(begin, end);
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent,
          typename T_SecondComponent,
          typename... T_Components>
void BasicScene<T_SceneComponents...>::removeComponents(uint64_t begin, uint64_t end)
{
    auto& v = std::get<std::vector<T_FirstComponent>&>(_components);
    v.erase(v.begin()+begin, v.begin()+end);
    removeComponents<T_SecondComponent, T_Components...>(begin, end);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::removeComponents(uint64_t begin, uint64_t end)
{
    auto& v = std::get<std::vector<T_Component>&>(_components);
    v.erase(v.begin()+begin, v.begin()+end);
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
bool BasicScene<T_SceneComponents...>::iterate(std::vector<T_FirstComponent>& firstVector,
                                               std::vector<T_SecondComponent>& secondVector,
                                               std::vector<T_Components>&... restVectors,
                                               CIter<T_FirstComponent>& firstIter,
                                               CIter<T_SecondComponent>& secondIter,
                                               CIter<T_Components>&... restIters,
                                               std::unordered_map<CId, uint64_t>& nIterations,
                                               uint64_t& maxIterations)
{
    uint64_t& nit = nIterations[Component::typeId<T_FirstComponent>()];

    firstIter += maxIterations-nit;
    nit = maxIterations;
    for (;firstIter != firstVector.end() && firstIter->_nodeId == NId(); ++firstIter, ++nit);

    if (firstIter == firstVector.end())
        return false;

    do {
        maxIterations = nit;
        if (!iterate<T_SecondComponent, T_Components...>(secondVector, restVectors...,
                                                         secondIter, restIters...,
                                                         nIterations, maxIterations))
            return false;

        firstIter += maxIterations-nit;
        nit = maxIterations;
        for (;firstIter != firstVector.end() && firstIter->_nodeId == NId(); ++firstIter, ++nit);

        if (firstIter == firstVector.end())
            return false;
    } while (maxIterations > nit);

    return true;
}

template <typename... T_SceneComponents>
template <typename T_Component>
bool BasicScene<T_SceneComponents...>::iterate(std::vector<T_Component>& vector,
                                               CIter<T_Component>& iter,
                                               std::unordered_map<CId, uint64_t>& nIterations,
                                               uint64_t& maxIterations)
{
    uint64_t& nit = nIterations[Component::typeId<T_Component>()];

    iter += maxIterations-nit;
    nit = maxIterations;
    for (;iter != vector.end() && iter->_nodeId == NId(); ++iter, ++nit);

    if (iter == vector.end())
        return false;

    maxIterations = nit;
    return true;
}
