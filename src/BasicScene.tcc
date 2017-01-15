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

    auto parentId = it->parent;
    std::vector<NId> children = it->children;

    for (auto& childId : children)
        removeNode(childId);

    it = _nodes.begin();
    findNode(id, it);

    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    decreaseNodeSize(parentIt);

    _nodes.erase(it);
}

template <typename... T_SceneComponents>
template <typename T_Visitor, typename... T_Components>
void BasicScene<T_SceneComponents...>::accept(Visitor<T_Visitor, T_Components...>& visitor)
{
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
void BasicScene<T_SceneComponents...>::decreaseNodeSize(NodeIterator& it)
{
    --it->size;
    if (it->parent == 0)
        return;
    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    increaseNodeSize(parentIt);
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
    nIt->_nodeId = _nodeId;
    addComponents<T_SecondComponent, T_Components...>(pos);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::addComponents(uint64_t pos)
{
    auto& v = std::get<std::vector<T_Component>&>(_components);
    auto nIt = v.insert(v.begin()+pos, T_Component());
    nIt->_nodeId = _nodeId;
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent, typename... T_Components>
void BasicScene<T_SceneComponents...>::setComponents(uint64_t pos,
                                                     T_FirstComponent&& firstComponent,
                                                     T_Components&&... components)
{
    auto& c = *(accessComponents<T_FirstComponent>().begin() + pos);
    NId nodeId = c._nodeId;
    c = std::forward<T_FirstComponent>(firstComponent);
    c._nodeId = nodeId;

    //  set rest of the components
    setComponents(pos, std::forward<T_Components>(components)...);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::setComponents(uint64_t pos, T_Component&& component)
{
    auto& c = *(accessComponents<T_Component>().begin() + pos);
    NId nodeId = c._nodeId;
    c = std::forward<T_Component>(component);
    c._nodeId = nodeId;
}

template <typename... T_SceneComponents>
template <typename... T_Components>
std::tuple<std::vector<T_Components>&...> BasicScene<T_SceneComponents...>::accessCollection(void)
{
    return std::tie(accessComponents<T_Components>()...);
}

template <typename... T_SceneComponents>
template <typename T_FirstComponent, typename... T_Components>
void BasicScene<T_SceneComponents...>::initIterators(std::vector<T_FirstComponent>& firstVector,
                                                     std::vector<T_Components>&... restVectors,
                                                     CIter<T_FirstComponent>& firstIter,
                                                     CIter<T_Components>&... restIters)
{
    firstIter = firstVector.begin();
    initIterators<T_Components...>(restVectors..., restIters...);
}

template <typename... T_SceneComponents>
template <typename T_Component>
void BasicScene<T_SceneComponents...>::initIterators(std::vector<T_Component>& vector,
                               CIter<T_Component>& iter)
{
    iter = vector.begin();
}


template <typename... T_SceneComponents>
template <typename T_FirstComponent, typename... T_Components>
bool BasicScene<T_SceneComponents...>::iterate(std::vector<T_FirstComponent>& firstVector,
                                               std::vector<T_Components>&... restVectors,
                                               CIter<T_FirstComponent>& firstIter,
                                               CIter<T_Components>&... restIters,
                                               NId& maxId)
{

    for (;firstIter != firstVector.end() && maxId > firstIter->_nodeId; ++firstIter);

    if (firstIter == firstVector.end())
        return false;

    maxId = firstIter->_nodeId;

    if (!iterate<T_Components...>(restVectors..., restIters..., maxId))
        return false;

    for (;firstIter != firstVector.end() && maxId > firstIter->_nodeId;) {
        for (;maxId > firstIter->_nodeId && firstIter != firstVector.end(); ++firstIter);
        if (firstIter == firstVector.end() || !iterate<T_Components...>(restVectors..., restIters..., maxId))
            return false;
        maxId = firstIter->_nodeId;
    }

    return true;
}

template <typename... T_SceneComponents>
template <typename T_Component>
bool BasicScene<T_SceneComponents...>::iterate(std::vector<T_Component>& vector,
                         CIter<T_Component>& iter,
                         NId& maxId)
{
    for (;iter != vector.end() && maxId > iter->_nodeId; ++iter);
    if (iter == vector.end())
        return false;
    maxId = iter->_nodeId;
    return true;
}
